#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX], work[MAX];
    int finish[MAX];
    int i, j;

    printf("Enter number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];  // initialize work
    }

    // Initialize finish array
    for(i = 0; i < n; i++) {
        int allZero = 1;
        for(j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                allZero = 0;
                break;
            }
        }
        finish[i] = allZero ? 1 : 0;
    }

    // Deadlock detection algorithm
    int changed = 1;
    while(changed) {
        changed = 0;

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int canExecute = 1;

                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if(canExecute) {
                    // Process completes, release resources
                    for(j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    }

    // Check for deadlock
    int deadlock = 0;
    printf("\nDeadlocked Processes: ");
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(!deadlock)
        printf("None (No Deadlock)");

    return 0;
}
