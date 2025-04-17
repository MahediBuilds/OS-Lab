#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    int allocation[n][m], request[n][m], available[m];
    int work[m];
    bool finish[n];

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter request matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter available matrix:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    for (i = 0; i < n; i++) {
        bool zero_allocation = true;
        for (j = 0; j < m; j++) {
            if (allocation[i][j] != 0) {
                zero_allocation = false;
                break;
            }
        }
        finish[i] = zero_allocation;
    }

    bool found_process;
    do {
        found_process = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    printf("Process %d can finish.\n", i);
                    found_process = true;
                }
            }
        }
    } while (found_process);

    bool deadlock = false;
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

    if (deadlock)
        printf("System is in a deadlock state.\n");
    else
        printf("System is not in a deadlock state.\n");

    return 0;
}

