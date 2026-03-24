#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rem_bt[n], ct[n], tat[n], wt[n], rt[n];
    int first_response[n];

    
    for (int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
        first_response[i] = -1;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    int gantt_p[100], gantt_t[100];
    int idx = 0;

    while (completed < n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && at[i] <= time) {
                done = 0;

               
                if (first_response[i] == -1) {
                    first_response[i] = time;
                    rt[i] = time - at[i];
                }

                gantt_p[idx] = i;
                gantt_t[idx] = time;
                idx++;

                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    ct[i] = time;
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if (done) {
            time++; 
        }
    }

    gantt_t[idx] = time; 

    
    printf("\nGantt Chart:\n");

    for (int i = 0; i < idx; i++) {
        printf("--------");
    }
    printf("-\n|");

    for (int i = 0; i < idx; i++) {
        printf("  P%d   |", gantt_p[i] + 1);
    }

    printf("\n");

    
    for (int i = 0; i < idx; i++) {
        printf("--------");
    }
    printf("-\n");

    for (int i = 0; i <= idx; i++) {
        printf("%-8d", gantt_t[i]);
    }
    printf("\n");

    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];
        total_rt += rt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage RT = %.2f\n", total_rt / n);

    return 0;
}
