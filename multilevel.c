
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
    int type;
} Process;

typedef struct {
    Process *queue[100];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Process *p) {
    if (q->rear == 99) return;
    if (q->front == -1) q->front = 0;
    q->queue[++q->rear] = p;
}

Process* dequeue(Queue *q) {
    Process *p = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return p;
}

int compareArrival(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrival - p2->arrival;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[100];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time: ");
        scanf("%d", &processes[i].burst);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &processes[i].type);
        processes[i].id = i;
        processes[i].remaining = processes[i].burst;
        processes[i].completion = 0;
    }

    qsort(processes, n, sizeof(Process), compareArrival);

    Queue systemQ, userQ;
    initQueue(&systemQ);
    initQueue(&userQ);

    int current_time = 0, completed = 0, i = 0;
    Process *current = NULL;

    while (completed < n) {
        // add arrivals
        while (i < n && processes[i].arrival <= current_time) {
            if (processes[i].type == 0)
                enqueue(&systemQ, &processes[i]);
            else
                enqueue(&userQ, &processes[i]);
            i++;
        }

        // preemption
        if (current != NULL && current->type == 1 && !isEmpty(&systemQ)) {
            enqueue(&userQ, current);
            current = NULL;
        }

        // select next
        if (current == NULL) {
            if (!isEmpty(&systemQ)) current = dequeue(&systemQ);
            else if (!isEmpty(&userQ)) current = dequeue(&userQ);
            else { current_time++; continue; }
        }

        // execute
        current->remaining--;
        current_time++;

        if (current->remaining == 0) {
            current->completion = current_time;
            current->turnaround = current->completion - current->arrival;
            current->waiting = current->turnaround - current->burst;
            completed++;
            current = NULL;
        }
    }

    // print results
    printf("\nID | Type   | AT | BT | CT | WT | TAT\n");
    double totalWT = 0, totalTAT = 0;
    for (int j = 0; j < n; j++) {
        printf("%d  | %s | %d  | %d  | %d  | %d  | %d\n",
               processes[j].id,
               processes[j].type == 0 ? "System" : "User",
               processes[j].arrival,
               processes[j].burst,
               processes[j].completion,
               processes[j].waiting,
               processes[j].turnaround);
        totalWT += processes[j].waiting;
        totalTAT += processes[j].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWT/n);
    printf("Average Turnaround Time: %.2f\n", totalTAT/n);

    return 0;
}
