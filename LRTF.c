#include <stdio.h>
#include <limits.h>
#include <string.h>

int main() {
    int n;

    printf("\nEnter number of processes: \n");
    scanf("%d", &n);

    char pid[n][10];  
    int at[n], bt[n];
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

    // 🔥 LRTF Logic
    while (completed != n) {

        int max_bt = -1;
        int max_index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_bt[i] > 0 && remaining_bt[i] > max_bt) {
                max_bt = remaining_bt[i];
                max_index = i;
            }
        }

        if (max_index == -1) {
            current_time++;
        } 
        else {

            if (is_first_response[max_index]) {
                rt[max_index] = current_time - at[max_index];
                is_first_response[max_index] = 0;
            }

            remaining_bt[max_index]--;
            current_time++;

            if (remaining_bt[max_index] == 0) {
                completed++;
                ct[max_index] = current_time;
                tat[max_index] = ct[max_index] - at[max_index];
                wt[max_index] = tat[max_index] - bt[max_index];
            }
        }
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%-5s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);
    }
}
