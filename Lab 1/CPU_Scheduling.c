#include <stdio.h>
#include <limits.h>

typedef struct {
    int id, arrival, burst, remaining, waiting, turnaround, completion, response, started;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

void fcfs(Process p[], int n) {
    sortByArrival(p, n);
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;

        p[i].response = time - p[i].arrival;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion;
    }
}

void sjfNonPreemptive(Process p[], int n) {
    int completed = 0, time = 0;

    while (completed < n) {
        int minIndex = -1, minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].completion == 0) {
                if (p[i].burst < minBurst || (p[i].burst == minBurst && p[i].arrival < p[minIndex].arrival)) {
                    minBurst = p[i].burst;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        p[minIndex].response = time - p[minIndex].arrival;
        time += p[minIndex].burst;
        p[minIndex].completion = time;
        p[minIndex].turnaround = p[minIndex].completion - p[minIndex].arrival;
        p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
        completed++;
    }
}

void sjfPreemptive(Process p[], int n) {
    int completed = 0, time = 0, minIndex = -1, minBurst = INT_MAX;

    while (completed < n) {
        minIndex = -1, minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].remaining < minBurst || (p[i].remaining == minBurst && p[i].arrival < p[minIndex].arrival)) {
                    minBurst = p[i].remaining;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        if (p[minIndex].started == 0) {
            p[minIndex].response = time - p[minIndex].arrival;
            p[minIndex].started = 1;
        }

        p[minIndex].remaining--;
        time++;

        if (p[minIndex].remaining == 0) {
            p[minIndex].completion = time;
            p[minIndex].turnaround = p[minIndex].completion - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
            completed++;
        }
    }
}

void displayResults(Process p[], int n, const char *title) {
    printf("\n--- %s ---\n", title);
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    float totalWT = 0, totalTAT = 0, totalRT = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting, p[i].response);
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
        totalRT += p[i].response;
    }

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Response Time: %.2f\n", totalRT / n);
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n], temp[n];

    printf("Enter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1; 
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].waiting = p[i].turnaround = p[i].completion = p[i].response = p[i].started = 0;
        temp[i] = p[i]; // Copy for reuse
    }

    while (1) {
        printf("\nCPU Scheduling Algorithms:\n");
        printf("1. First Come First Serve (FCFS)\n");
        printf("2. Shortest Job First (Non-Preemptive)\n");
        printf("3. Shortest Job First (Preemptive)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        for (int i = 0; i < n; i++) p[i] = temp[i]; // Restore original processes

        switch (choice) {
            case 1:
                fcfs(p, n);
                displayResults(p, n, "First Come First Serve (FCFS)");
                break;
            case 2:
                sjfNonPreemptive(p, n);
                displayResults(p, n, "Shortest Job First (Non-Preemptive)");
                break;
            case 3:
                sjfPreemptive(p, n);
                displayResults(p, n, "Shortest Job First (Preemptive)");
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
