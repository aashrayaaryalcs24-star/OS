#include<stdio.h>

int main()
{
    int n, tq;
    int at[20], bt[20], rt[20];
    int wt[20], tat[20], rtim[20]={0}, ct[20];
    int q[100], front=0, rear=0;
    int visited[20]={0};

    int time=0, completed=0;

    int gantt_p[100], gantt_t[100];
    int g = 0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("Arrival Time and Burst Time for P%d: ",i+1);
        scanf("%d%d",&at[i],&bt[i]);
        rt[i]=bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    while(completed<n)
    {

        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && !visited[i])
            {
                q[rear++]=i;
                visited[i]=1;
            }
        }

        if(front==rear)
        {
            time++;
            continue;
        }

        int i = q[front++];

        if(rtim[i]==0)
            rtim[i]=time-at[i];

        gantt_p[g] = i;
        gantt_t[g] = time;
        g++;

        if(rt[i] > tq)
        {
            time += tq;
            rt[i] -= tq;
        }
        else
        {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        for(int j=0;j<n;j++)
        {
            if(at[j]<=time && !visited[j])
            {
                q[rear++]=j;
                visited[j]=1;
            }
        }

        if(rt[i] > 0)
            q[rear++]=i;
    }

   
    gantt_t[g] = time;

    printf("\nGantt Chart:\n");

    for(int i=0;i<g;i++)
        printf("| P%d ", gantt_p[i]+1);
    printf("|\n");

    for(int i=0;i<=g;i++)
        printf("%d    ", gantt_t[i]);
    printf("\n");

    float awt=0, atat=0, art=0;

    printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        awt+=wt[i];
        atat+=tat[i];
        art+=rtim[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], wt[i], tat[i], rtim[i]);
    }

    printf("\nAverage WT = %.2f",awt/n);
    printf("\nAverage TAT = %.2f",atat/n);
    printf("\nAverage RT = %.2f\n",art/n);

    return 0;
}
