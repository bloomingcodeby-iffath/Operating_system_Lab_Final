#include<stdio.h>
#include<string.h>
int main(){
    int n;
    printf("\nEnter number of Processes: \n");
    scanf("%d",&n);

    char pid[n][10];
    int at[n],bt[n];
    int ct[n], tat[n], wt[n], rt[n];

    printf("\nEnter Processes-P1 P2 ..Pn :\n");
    for(int i=0;i<n;i++) scanf("%s",pid[i]);

    printf("\nEnter Arrival Times: \n");
    for(int i=0;i<n;i++) scanf("%d",&at[i]);

    printf("\nEnter Burst Times:\n");
    for (int i = 0; i < n; i++)scanf("%d", &bt[i]);
    
    //Sorting
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(at[i]>at[j]){

                int temp=at[i];
                at[i]=at[j];
                at[j]=temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                char temp_pid[10];
                strcpy(temp_pid, pid[i]);
                strcpy(pid[i], pid[j]);
                strcpy(pid[j], temp_pid);
            }
        }
    }
    //FCFS Calculation
    int current_time=0;

    for(int i=0;i<n;i++){

      if(current_time<at[i]) current_time=at[i];
      wt[i]=current_time-at[i];
      rt[i]=wt[i];
      current_time+=bt[i];
      ct[i]=current_time;
      tat[i]=ct[i]-at[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",pid[i], at[i], bt[i],ct[i], tat[i], wt[i], rt[i]);
    }
}
