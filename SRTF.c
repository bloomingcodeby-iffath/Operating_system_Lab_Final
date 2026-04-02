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

    //Input Section 

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

    // SRTF Logic 

    while (completed != n) {

        int min_bt = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
            min_bt = remaining_bt[i];
            min_index = i;
            }
        }

        if (min_index == -1) {
            current_time++;
        } 
        else {

            if (is_first_response[min_index]) {
                rt[min_index] = current_time - at[min_index];
                is_first_response[min_index] = 0;
            }

            remaining_bt[min_index]--;
            current_time++;

            if (remaining_bt[min_index] == 0) {
                completed++;
                ct[min_index] = current_time;
                tat[min_index] = ct[min_index] - at[min_index];
                wt[min_index] = tat[min_index] - bt[min_index];
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