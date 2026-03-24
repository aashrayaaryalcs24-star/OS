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
    int completion_time;
    int waiting_time;
    int turnaround_time;
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

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process process_list[MAX];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &process_list[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d", &process_list[i].burst_time);
        printf("Enter type (0 = System, 1 = User): ");
        int t;
        scanf("%d", &t);
        if (t == 0) strcpy(process_list[i].type, "System");
        else strcpy(process_list[i].type, "User");

        process_list[i].process_id = i;
        process_list[i].remaining_time = process_list[i].burst_time;
        process_list[i].completion_time = 0;
        process_list[i].waiting_time = 0;
        process_list[i].turnaround_time = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (process_list[i].arrival_time > process_list[j].arrival_time) {
                Process temp = process_list[i];
                process_list[i] = process_list[j];
                process_list[j] = temp;
            }
        }
    }

    Queue systemQueue, userQueue;
    initQueue(&systemQueue);
    initQueue(&userQueue);

    int current_time = 0, completed = 0, i = 0;
    Process *current_process = NULL;

    int gantt[MAX];
    int gantt_time[MAX];
    int gantt_index = 0;

    while (completed < n) {
        while (i < n && process_list[i].arrival_time <= current_time) {
            if (strcmp(process_list[i].type, "System") == 0) {
                enqueue(&systemQueue, process_list[i]);
            } else {
                enqueue(&userQueue, process_list[i]);
            }
            i++;
        }

        if (current_process != NULL) {
            if (strcmp(current_process->type, "User") == 0 && !isEmpty(&systemQueue)) {
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
        gantt[gantt_index] = current_process->process_id;
        gantt_time[gantt_index] = current_time;
        gantt_index++;
        current_time++;

        if (current_process->remaining_time == 0) {
            current_process->completion_time = current_time;
            // Update original list
            for (int k = 0; k < n; k++) {
                if (process_list[k].process_id == current_process->process_id) {
                    process_list[k].completion_time = current_process->completion_time;
                    process_list[k].turnaround_time = process_list[k].completion_time - process_list[k].arrival_time;
                    process_list[k].waiting_time = process_list[k].turnaround_time - process_list[k].burst_time;
                }
            }
            completed++;
            free(current_process);
            current_process = NULL;
        }
    }

    printf("\nID   Type    AT   BT   CT   WT   TAT\n");
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d    %-6s %2d   %2d   %2d   %2d   %2d\n",
               process_list[i].process_id,
               process_list[i].type,
               process_list[i].arrival_time,
               process_list[i].burst_time,
               process_list[i].completion_time,
               process_list[i].waiting_time,
               process_list[i].turnaround_time);
        totalWT += process_list[i].waiting_time;
        totalTAT += process_list[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    printf("\nGantt Chart:\n");
    for (int j = 0; j < gantt_index; j++) {
        printf("| P%d ", gantt[j]);
    }
    printf("|\n");

    for (int j = 0; j < gantt_index; j++) {
        printf("%d    ", gantt_time[j]);
    }
    printf("%d\n", current_time);

    return 0;
}
