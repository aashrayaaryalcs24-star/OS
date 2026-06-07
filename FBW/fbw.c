#include <stdio.h>

void firstFit(int b[], int m, int p[], int n) {
    int a[n];
    for(int i=0;i<n;i++) a[i]=-1;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(b[j]>=p[i]) {
                a[i]=j;
                b[j]=0;
                break;
            }

    printf("\nFirst Fit:\n");
    for(int i=0;i<n;i++)
        if(a[i]!=-1)
            printf("Process %d -> Block %d\n",i+1,a[i]+1);
        else
            printf("Process %d -> Not Allocated\n",i+1);
}

void bestFit(int b[], int m, int p[], int n) {
    int a[n];
    for(int i=0;i<n;i++) a[i]=-1;

    for(int i=0;i<n;i++) {
        int best=-1;
        for(int j=0;j<m;j++)
            if(b[j]>=p[i] && (best==-1 || b[j]<b[best]))
                best=j;

        if(best!=-1) {
            a[i]=best;
            b[best]=0;
        }
    }

    printf("\nBest Fit:\n");
    for(int i=0;i<n;i++)
        if(a[i]!=-1)
            printf("Process %d -> Block %d\n",i+1,a[i]+1);
        else
            printf("Process %d -> Not Allocated\n",i+1);
}

void worstFit(int b[], int m, int p[], int n) {
    int a[n];
    for(int i=0;i<n;i++) a[i]=-1;

    for(int i=0;i<n;i++) {
        int worst=-1;
        for(int j=0;j<m;j++)
            if(b[j]>=p[i] && (worst==-1 || b[j]>b[worst]))
                worst=j;

        if(worst!=-1) {
            a[i]=worst;
            b[worst]=0;
        }
    }

    printf("\nWorst Fit:\n");
    for(int i=0;i<n;i++)
        if(a[i]!=-1)
            printf("Process %d -> Block %d\n",i+1,a[i]+1);
        else
            printf("Process %d -> Not Allocated\n",i+1);
}

int main() {
    int m,n;

    printf("Enter number of blocks: ");
    scanf("%d",&m);

    int b[m];
    printf("Enter block sizes:\n");
    for(int i=0;i<m;i++)
        scanf("%d",&b[i]);

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int p[n];
    printf("Enter process sizes:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    int b1[m],b2[m],b3[m];

    for(int i=0;i<m;i++) {
        b1[i]=b[i];
        b2[i]=b[i];
        b3[i]=b[i];
    }

    firstFit(b1,m,p,n);
    bestFit(b2,m,p,n);
    worstFit(b3,m,p,n);

    return 0;
}
