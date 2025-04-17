#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    int alloc[n][m], request[n][m], avail[m];
    bool finish[n];

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter request matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter available matrix:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for (i = 0; i < n; i++) {
        bool is_zero = true;
        for (j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                is_zero = false;
                break;
            }
        }
        finish[i] = is_zero;
    }

    bool changed;
    do {
        changed = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_finish = true;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > avail[j]) {
                        can_finish = false;
                        break;
                    }
                }

                if (can_finish) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    finish[i] = true;
                    changed = true;
                    printf("Process %d can finish.\n", i);
                }
            }
        }
    } while (changed);

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
