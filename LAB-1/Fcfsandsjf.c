#include <stdio.h>

#define MAX 20

void fcfs(int n, int at[], int bt[])
{

    int wt[MAX], tat[MAX], ct[MAX], rt[MAX];
    int time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++)
    {

        if (time < at[i])
            time = at[i];

        rt[i] = time - at[i]; // Response Time
        wt[i] = rt[i];        // For FCFS, RT = WT

        time += bt[i];
        ct[i] = time; // Completion Time
        tat[i] = ct[i] - at[i];

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\n--- FCFS ---\n");
    printf("PID\tAT\tBT\tCT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);
}

void sjf_nonpreemptive(int n, int at[], int bt[])
{

    int wt[MAX] = {0}, tat[MAX] = {0}, ct[MAX] = {0}, rt[MAX] = {0};
    int completed[MAX] = {0};
    int time = 0, count = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    while (count < n)
    {

        int min = 9999, idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && !completed[i])
            {
                if (bt[i] < min)
                {
                    min = bt[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {

            rt[idx] = time - at[idx]; // Response Time
            wt[idx] = rt[idx];

            time += bt[idx];
            ct[idx] = time; // Completion Time
            tat[idx] = ct[idx] - at[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];
            total_rt += rt[idx];

            completed[idx] = 1;
            count++;
        }
        else
        {
            time++;
        }
    }

    printf("\n--- SJF Non-Preemptive ---\n");
    printf("PID\tAT\tBT\tCT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);
}

void sjf_preemptive(int n, int at[], int bt[])
{

    int rt_rem[MAX], wt[MAX] = {0}, tat[MAX] = {0};
    int ct[MAX] = {0}, rt[MAX];
    int first_start[MAX];

    for (int i = 0; i < n; i++)
    {
        rt_rem[i] = bt[i];
        first_start[i] = -1;
    }

    int complete = 0, time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    while (complete < n)
    {

        int min = 9999, idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rt_rem[i] > 0)
            {
                if (rt_rem[i] < min)
                {
                    min = rt_rem[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        if (first_start[idx] == -1)
            first_start[idx] = time; // First response time capture

        rt_rem[idx]--;
        time++;

        if (rt_rem[idx] == 0)
        {

            complete++;
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            rt[idx] = first_start[idx] - at[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];
            total_rt += rt[idx];
        }
    }

    printf("\n--- SJF Preemptive (SRTF) ---\n");
    printf("PID\tAT\tBT\tCT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);
}

int main()
{
    int n, choice;
    int at[MAX], bt[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }
    printf("\nChoose Algorithm:");
    printf("\n1. FCFS");
    printf("\n2. SJF Non-Preemptive");
    printf("\n3. SJF Preemptive (SRTF)");
    printf("\nEnter choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        fcfs(n, at, bt);
        break;
    case 2:
        sjf_nonpreemptive(n, at, bt);
        break;
    case 3:
        sjf_preemptive(n, at, bt);
        break;
    default:
        printf("Invalid choice");
    }
    return 0;
}
