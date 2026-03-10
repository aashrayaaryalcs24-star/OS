#include <stdio.h>

int main() {
    int n, i;
    int bt[20], wt[20], tat[20], ct[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Completion time calculation
    ct[0] = bt[0];
    for (i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i];
    }

    // Turnaround time and waiting time
    for (i = 0; i < n; i++) {
        tat[i] = ct[i];          // since arrival time = 0
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}