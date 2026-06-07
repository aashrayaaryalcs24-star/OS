#include <stdio.h>
#define MAX 10
int n, m, alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];
int isSafe() {
    int work[MAX], finish[MAX] = {0}, seq[MAX], i, j, count = 0;

    for (i = 0; i < m; i++) work[i] = avail[i];

    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                for (j = 0; j < m && need[i][j] <= work[j]; j++);
                if (j == m) {
                    for (j = 0; j < m; j++) work[j] += alloc[i][j];
                    seq[count++] = i;
                    finish[i] = found = 1;
                }
            }
        }
        if (!found) return 0;
    }

    printf("\nSafe Sequence: ");
    for (i = 0; i < n; i++) printf("P%d ", seq[i]);
    printf("\n");
    return 1;
}

int main() {
    int i, j, pid, request[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++) scanf("%d", &avail[i]);

    printf("\nNEED Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    if (isSafe())
        printf("\nSystem is initially in SAFE state\n");
    else {
        printf("\nSystem is NOT SAFE\n");
        return 0;
    }

    printf("\nEnter process number making request: ");
    scanf("%d", &pid);

    printf("Enter request vector:\n");
    for (i = 0; i < m; i++) scanf("%d", &request[i]);

    for (i = 0; i < m; i++)
        if (request[i] > need[pid][i]) {
            printf("\nError: Request exceeds maximum need\n");
            return 0;
        }

    for (i = 0; i < m; i++)
        if (request[i] > avail[i]) {
            printf("\nResources not available. Process must wait\n");
            return 0;
        }

    for (i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if (isSafe())
        printf("\nRequest can be granted (SAFE)\n");
    else {
        printf("\nRequest cannot be granted (UNSAFE)\n");
        for (i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
    }

    return 0;
}
