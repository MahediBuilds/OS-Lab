#include <stdio.h>

int main() {
    int n, frames, i, j, k, found, index = 0, page_faults = 0, hits = 0;
    char pages[100];
    
    printf("Enter the size of the pages:\n");
    scanf("%d", &n);
    printf("Enter the page strings:\n");
    scanf("%s", pages);
    printf("Enter the no of page frames:\n");
    scanf("%d", &frames);

    int mem[frames];
    for (i = 0; i < frames; i++) mem[i] = -1;

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (mem[j] == pages[i] - '0') {
                hits++;
                found = 1;
                break;
            }
        }
        if (!found) {
            mem[index] = pages[i] - '0';
            index = (index + 1) % frames;
            page_faults++;
        }
    }

    printf("FIFO Page Faults: %d, Page Hits: %d\n", page_faults, hits);
    return 0;
}