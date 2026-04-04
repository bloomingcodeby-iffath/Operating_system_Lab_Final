#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int total[m], avail[m];

    // Input
    printf("\nEnter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("\nEnter total instances:\n");
    for(i=0;i<m;i++)
        scanf("%d",&total[i]);

    // Need
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Available
    for(j=0;j<m;j++){
        int sum=0;
        for(i=0;i<n;i++)
            sum += alloc[i][j];
        avail[j] = total[j] - sum;
    }

    // Header
    printf("\nStep|P |Allocation| Max |Need|Avail.Before |Avail.After\n");

    int finish[n], safeSeq[n];
    for(i=0;i<n;i++) finish[i]=0;

    int count=0;

    while(count < n){
        int found=0;

        for(i=0;i<n;i++){
            if(finish[i]==0){

                int flag=1;
                for(j=0;j<m;j++){
                    if(need[i][j] > avail[j]){
                        flag=0;
                        break;
                    }
                }

                if(flag==1){

                    int before[m];
                    for(j=0;j<m;j++)
                        before[j] = avail[j];

                    // Step & Process
                    printf("%d   | P%d | ", count+1, i);

                    // Allocation
                    for(j=0;j<m;j++)
                        printf("%d ", alloc[i][j]);
                    printf("| ");

                    // Max
                    for(j=0;j<m;j++)
                        printf("%d ", max[i][j]);
                    printf("| ");

                    // Need
                    for(j=0;j<m;j++)
                        printf("%d ", need[i][j]);
                    printf("| ");

                    // Available Before
                    for(j=0;j<m;j++)
                        printf("%d ", before[j]);
                    printf("| ");

                    // Update Available
                    for(k=0;k<m;k++)
                        avail[k] += alloc[i][k];

                    // Available After
                    for(j=0;j<m;j++)
                        printf("%d ", avail[j]);

                    printf("\n");

                    finish[i]=1;
                    safeSeq[count++] = i;

                    for(j=0;j<m;j++)
                        need[i][j]=0;

                    found=1;
                }
            }
        }

        if(found==0){
            printf("\nSystem is NOT in safe state!\n");
            return 0;
        }
    }

    // Safe sequence
    printf("\nSAFE sequence: ");
    for(i=0;i<n;i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    return 0;
}
