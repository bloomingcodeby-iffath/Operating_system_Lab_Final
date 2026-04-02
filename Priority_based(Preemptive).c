#include <stdio.h>
#include <limits.h>
#include <string.h>

int main() {
    int n;

    printf("\nEnter number of processes: \n");
    scanf("%d", &n);

    char pid[n][10];  
    int at[n], bt[n], priority[n];
    int ct[n], tat[n], wt[n], rt[n];
    int remaining_bt[n];
    int completed = 0, current_time = 0;
    int is_first_response[n];

    // Input
    printf("\nEnter all PID (P1 P2 P3 ...Pn):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", pid[i]);
    }

    printf("\nEnter Arrival Times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("\nEnter Burst Times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        remaining_bt[i] = bt[i];
        is_first_response[i] = 1;
    }

    printf("\nEnter Priorities (lower value = higher priority):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    // 🔥 Preemptive Priority Logic
    while (completed != n) {

        int highest_priority = INT_MAX;
        int index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_bt[i] > 0) {

                if (priority[i] < highest_priority) {
                    highest_priority = priority[i];
                    index = i;
                }
                // Tie-breaker (optional but good)
                else if (priority[i] == highest_priority) {
                    if (remaining_bt[i] < remaining_bt[index]) {
                        index = i;
                    }
                }
            }
        }

        if (index == -1) {
            current_time++;
        } 
        else {

            if (is_first_response[index]) {
                rt[index] = current_time - at[index];
                is_first_response[index] = 0;
            }

            remaining_bt[index]--;
            current_time++;

            if (remaining_bt[index] == 0) {
                completed++;
                ct[index] = current_time;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];
            }
        }
    }

    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%-5s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], priority[i],
               ct[i], tat[i], wt[i], rt[i]);
    }
}
