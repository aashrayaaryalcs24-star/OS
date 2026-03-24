#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    char type[10];
} Process;

typedef struct {
    Process queue[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Process p) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->queue[++q->rear] = p;
}

Process dequeue(Queue *q) {
    Process p = q->queue[q->front];
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
    return p1->arrival_time - p2->arrival_time;
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    Process process_list[MAX];
    for (int i = 0; i < n; i++) {
        printf("Enter process_id, arrival_time, burst_time, type(system/user): ");
        scanf("%d %d %d %s", &process_list[i].process_id,
              &process_list[i].arrival_time,
              &process_list[i].burst_time,
              process_list[i].type);
        process_list[i].remaining_time = process_list[i].burst_time;
    }

    qsort(process_list, n, sizeof(Process), compareArrival);

    Queue systemQueue, userQueue;
    initQueue(&systemQueue);
    initQueue(&userQueue);

    int current_time = 0, completed = 0, i = 0;
    Process *current_process = NULL;

    while (completed < n) {
        while (i < n && process_list[i].arrival_time <= current_time) {
            if (strcmp(process_list[i].type, "system") == 0) {
                enqueue(&systemQueue, process_list[i]);
            } else {
                enqueue(&userQueue, process_list[i]);
            }
            i++;
        }

        if (current_process != NULL) {
            if (strcmp(current_process->type, "user") == 0 && !isEmpty(&systemQueue)) {
                enqueue(&userQueue, *current_process);
                current_process = NULL;
            }
        }

        if (current_process == NULL) {
            if (!isEmpty(&systemQueue)) {
                Process p = dequeue(&systemQueue);
                current_process = (Process *)malloc(sizeof(Process));
                *current_process = p;
            } else if (!isEmpty(&userQueue)) {
                Process p = dequeue(&userQueue);
                current_process = (Process *)malloc(sizeof(Process));
                *current_process = p;
            } else {
                current_time++;
                continue;
            }
        }

        current_process->remaining_time--;
        current_time++;

        if (current_process->remaining_time == 0) {
            printf("Process %d completed at time %d\n",
                   current_process->process_id, current_time);
            completed++;
            free(current_process);
            current_process = NULL;
        }
    }

    return 0;
}
