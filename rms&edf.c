#include <stdio.h>
#include <math.h>

#define MAX 10

int n;
int bt[MAX], deadline[MAX], period[MAX];

void edf() {
    double util = 0;
    for (int i = 0; i < n; i++)
        util += (double)bt[i] / period[i];

    printf("\n====== Earliest Deadline First (EDF) Scheduling ======\n");
    printf("CPU Utilization: %.2f\n", util);

    if (util > 1.0) {
        printf("NOT Schedulable (Utilization > 1)\n");
        return;
    }

    printf("Schedulable (Utilization <= 1)\n");

    int ct[MAX], wt[MAX], tat[MAX], order[MAX];
    for (int i = 0; i < n; i++) order[i] = i;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (deadline[order[i]] > deadline[order[j]]) {
                int t = order[i]; order[i] = order[j]; order[j] = t;
            }

    int time = 0;
    for (int i = 0; i < n; i++) {
        wt[order[i]] = time;
        time += bt[order[i]];
        ct[order[i]] = time;
        tat[order[i]] = ct[order[i]];
    }

    printf("ID  BF  Deadline  CT  WT  TAT\n");
    for (int i = 0; i < n; i++)
        printf("%d   %d   %d         %d   %d   %d\n",
               i, bt[i], deadline[i], ct[i], wt[i], tat[i]);
}

void rms() {
    double util = 0;
    for (int i = 0; i < n; i++)
        util += (double)bt[i] / period[i];

    double bound = n * (pow(2.0, 1.0 / n) - 1.0);

    printf("\n====== Rate Monotonic Scheduling (RMS) ======\n");
    printf("CPU Utilization: %.2f\n", util);
    printf("RM Bound: %.4f\n", bound);

    if (util > bound) {
        printf("NOT Schedulable (Utilization > RM Bound)\n");
        return;
    }

    printf("Schedulable (Utilization <= RM Bound)\n");

    int ct[MAX], wt[MAX], tat[MAX], order[MAX];
    for (int i = 0; i < n; i++) order[i] = i;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (period[order[i]] > period[order[j]]) {
                int t = order[i]; order[i] = order[j]; order[j] = t;
            }

    int time = 0;
    for (int i = 0; i < n; i++) {
        wt[order[i]] = time;
        time += bt[order[i]];
        ct[order[i]] = time;
        tat[order[i]] = ct[order[i]];
    }

    printf("ID  BF  Period  CT  WT  TAT\n");
    for (int i = 0; i < n; i++)
        printf("%d   %d   %d       %d   %d   %d\n",
               i, bt[i], period[i], ct[i], wt[i], tat[i]);
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");         scanf("%d", &bt[i]);
        printf("Deadline (for EDF): "); scanf("%d", &deadline[i]);
        printf("Period (for RMS): ");   scanf("%d", &period[i]);
    }

    edf();
    rms();

    return 0;
}
