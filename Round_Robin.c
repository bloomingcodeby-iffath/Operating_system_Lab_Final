#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    char pid[MAX][10];
    int at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], tat[MAX], wt[MAX], response[MAX];
    int inQueue[MAX] = {0};

    printf("Enter Process IDs (P1 P2 ..Pn):\n");
    for(int i = 0; i < n; i++)
        scanf("%s", pid[i]);

    printf("Enter Arrival Times:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &at[i]);

    printf("Enter Burst Times:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        response[i] = -1;   
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int queue[MAX];
    int front = 0, rear = 0;

    int time = 0, completed = 0;

    // Insert first arriving process
    queue[rear++] = 0;
    inQueue[0] = 1;
    time = at[0];

    while(completed < n) {

        int i = queue[front++];   // dequeue

        // First response time
        if(response[i] == -1)
            response[i] = time - at[i];

        if(rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        // Check newly arrived processes
        for(int j = 0; j < n; j++) {
            if(at[j] <= time && rt[j] > 0 && inQueue[j] == 0) {
                queue[rear++] = j;
                inQueue[j] = 1;
            }
        }

        // If current process not finished → push back
        if(rt[i] > 0) {
            queue[rear++] = i;
        }

        // If queue empty but process left
        if(front == rear) {
            for(int j = 0; j < n; j++) {
                if(rt[j] > 0) {
                    queue[rear++] = j;
                    inQueue[j] = 1;
                    time = at[j];
                    break;
                }
            }
        }
    }

    // Calculate TAT & WT
    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], response[i]);
    }

    return 0;
}