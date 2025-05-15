#include <stdio.h>

int main() {
    int n, frames, i, j, k, page_faults = 0, hits = 0;

    printf("Enter the size of the pages:\n");
    scanf("%d", &n);

    char pages[n + 1];
    printf("Enter the page strings:\n");
    scanf("%s", pages);

    printf("Enter the no of page frames:\n");
    scanf("%d", &frames);

    int mem[frames], next_use[frames];
    for (i = 0; i < frames; i++) {
        mem[i] = -1;
    }

    for (i = 0; i < n; i++) {
        int page = pages[i] - '0';
        int found = 0;

        for (j = 0; j < frames; j++) {
            if (mem[j] == page) {
                hits++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (page_faults < frames) {
                mem[page_faults++] = page;
            } else {
                for (j = 0; j < frames; j++) {
                    next_use[j] = -1;
                    for (k = i + 1; k < n; k++) {
                        if (mem[j] == pages[k] - '0') {
                            next_use[j] = k;
                            break;
                        }
                    }
                }

                int farthest = 0;
                for (j = 1; j < frames; j++) {
                    if (next_use[j] > next_use[farthest]) {
                        farthest = j;
                    }
                }

                mem[farthest] = page;
                page_faults++;
            }
        }
    }

    printf("Optimal Page Faults: %d, Page Hits: %d\n", page_faults, hits);
    return 0;
}
