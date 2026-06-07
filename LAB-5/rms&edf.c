#include <stdio.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period;
    int ct, wt, tat;
    int completed;
} Process;

void printGantt(int gantt[], int size) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < size; i++) {
        printf(" P%d |", gantt[i]);
    }

    printf("\n0");
    for (int i = 0; i < size; i++) {
        printf("   %d", i + 1);
    }
    printf("\n");
}

void edf(Process p[], int n) {
    int time = 0, completed = 0;
    int gantt[100], g = 0;

    while (completed < n) {
        int idx = -1;
        int earliest = 9999;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].deadline < earliest) {
                earliest = p[i].deadline;
                idx = i;
            }
        }

        if (idx == -1) break;  // safety check

        for (int t = 0; t < p[idx].bt; t++) {
            gantt[g++] = p[idx].id;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;
        completed++;
    }

    printf("\n===== EDF Scheduling =====\n");
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    }

    printGantt(gantt, g);
}

void rms(Process p[], int n) {
    int time = 0, completed = 0;
    int gantt[100], g = 0;

    while (completed < n) {
        int idx = -1;
        int shortest = 9999;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].period < shortest) {
                shortest = p[i].period;
                idx = i;
            }
        }

        if (idx == -1) break;  // safety check

        for (int t = 0; t < p[idx].bt; t++) {
            gantt[g++] = p[idx].id;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;
        completed++;
    }

    printf("\n===== RMS Scheduling =====\n");
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }

    printGantt(gantt, g);
}

void reset(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].ct = p[i].wt = p[i].tat = 0;
        p[i].completed = 0;
    }
}

int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i;

        printf("\nProcess %d\n", i);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (RMS): ");
        scanf("%d", &p[i].period);

        p[i].completed = 0;
    }

    edf(p, n);
    reset(p, n);

    rms(p, n);

    return 0;
}
