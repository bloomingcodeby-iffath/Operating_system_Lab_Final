#include<stdio.h>
#include<string.h>

int main(){
    int n;
    printf("\nEnter number of Processes: \n");
    scanf("%d",&n);

    char pid[n][10];
    int at[n], bt[n];
    int ct[n], tat[n], wt[n], rt[n];
    int is_completed[n];

    printf("Enter Processes-P1 P2 ..Pn :\n");
    for(int i=0;i<n;i++) scanf("%s",pid[i]);

    printf("\nEnter Arrival Times: \n");
    for(int i=0;i<n;i++) scanf("%d",&at[i]);

    printf("\nEnter Burst Times:\n");
    for (int i = 0; i < n; i++) scanf("%d", &bt[i]);

    for(int i=0;i<n;i++) is_completed[i]=0;

    int completed = 0, current_time = 0;

    while(completed != n){
        int idx = -1;
        int max_bt = -1; // for LJF

        // Find process with MAX BT among arrived processes
        for(int i=0;i<n;i++){
            if(at[i] <= current_time && is_completed[i] == 0){
                if(bt[i] > max_bt){
                    max_bt = bt[i];
                    idx = i;
                }
                else if(bt[i] == max_bt){
                    if(at[i] < at[idx])
                        idx = i;
                }
            }
        }

        if(idx != -1){
            if(current_time < at[idx])
                current_time = at[idx];

            wt[idx] = current_time - at[idx];
            rt[idx] = wt[idx];

            current_time += bt[idx];
            ct[idx] = current_time;

            tat[idx] = ct[idx] - at[idx];

            is_completed[idx] = 1;
            completed++;
        }
        else{
            current_time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
}
