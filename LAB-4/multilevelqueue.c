#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
    char type[10];
} Process;

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1);
}

void enqueue(Queue *q, int val) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = val;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

void sortByArrival(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("PID: ");
        scanf("%d", &p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Type (system/user): ");
        scanf("%s", p[i].type);

        p[i].remaining = p[i].burst;
    }

    sortByArrival(p, n);

    Queue systemQ, userQ;
    initQueue(&systemQ);
    initQueue(&userQ);

    int time = 0, completed = 0, i = 0;
    int current = -1;

    int gantt[MAX], g_time[MAX];
    int g_index = 0;

    while (completed < n) {

        while (i < n && p[i].arrival <= time) {
            if (strcmp(p[i].type, "system") == 0)
                enqueue(&systemQ, i);
            else
                enqueue(&userQ, i);
            i++;
        }

        if (current != -1) {
            if (strcmp(p[current].type, "user") == 0 &&
                !isEmpty(&systemQ)) {
                enqueue(&userQ, current);
                current = -1;
            }
        }

        if (current == -1) {
            if (!isEmpty(&systemQ))
                current = dequeue(&systemQ);
            else if (!isEmpty(&userQ))
                current = dequeue(&userQ);
            else {
                time++;
                continue;
            }
        }

        gantt[g_index] = current;
        g_time[g_index] = time;
        g_index++;

        p[current].remaining--;
        time++;

        if (p[current].remaining == 0) {
            p[current].completion = time;
            completed++;
            current = -1;
        }
    }

    g_time[g_index] = time;

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }


    printf("\n\nGantt Chart:\n|");
    for (int i = 0; i < g_index; i++) {
        printf(" P%d |", p[gantt[i]].pid);
    }

    printf("\n%d", g_time[0]);
    for (int i = 1; i <= g_index; i++) {
        printf(" %d", g_time[i]);
    }

    printf("\n\nPID\tType\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].type,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
