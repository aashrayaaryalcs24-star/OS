#include <stdio.h>
#include <stdbool.h>


void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) printf("[ ] ");
        else printf("[%d] ", frames[i]);
    }
    printf("\n");
}

bool isHit(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) return true;
    }
    return false;
}


void fifo(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0, front = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\n--- FIFO Replacement Steps ---\n");
    for (int i = 0; i < n; i++) {
        if (!isHit(frames, capacity, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % capacity;
            faults++;
            printFrames(frames, capacity);
        }
    }
    printf("Total FIFO Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int capacity) {
    int frames[capacity], time[capacity], faults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\n--- LRU Replacement Steps ---\n");
    for (int i = 0; i < n; i++) {
        if (!isHit(frames, capacity, pages[i])) {
            int replace_idx = 0, min_time = i;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) { replace_idx = j; break; }
                if (time[j] < min_time) {
                    min_time = time[j];
                    replace_idx = j;
                }
            }
            frames[replace_idx] = pages[i];
            time[replace_idx] = i;
            faults++;
            printFrames(frames, capacity);
        } else {

            for (int j = 0; j < capacity; j++) {
                if (frames[j] == pages[i]) time[j] = i;
            }
        }
    }
    printf("Total LRU Page Faults: %d\n", faults);
}

                              
void optimal(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\n--- Optimal Replacement Steps ---\n");
    for (int i = 0; i < n; i++) {
        if (!isHit(frames, capacity, pages[i])) {
            int replace_idx = -1, farthest = i;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) { replace_idx = j; break; }
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) break;
                }
                if (k > farthest) {
                    farthest = k;
                    replace_idx = j;
                }
            }
            frames[replace_idx] = pages[i];
            faults++;
            printFrames(frames, capacity);
        }
    }
    printf("Total Optimal Page Faults: %d\n", faults);
}

int main() {
    int n, capacity;

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string (separated by spaces): ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);

    return 0;
}
