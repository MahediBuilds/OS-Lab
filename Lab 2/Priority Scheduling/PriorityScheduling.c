#include <limits.h>
#include <stdio.h>

struct Process {
  int id, arrivalTime, burstTime, priority;
  int completionTime, turnaroundTime, waitingTime, responseTime;
};

void swap(struct Process *a, struct Process *b) {
  struct Process temp = *a;
  *a = *b;
  *b = temp;
}

void sortByArrival(struct Process proc[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (proc[i].arrivalTime > proc[j].arrivalTime) {
        swap(&proc[i], &proc[j]);
      }
    }
  }
}

void prioritySchedulingNonPreemptive(struct Process proc[], int n) {
  int time = 0, completed = 0;
  float totalTAT = 0, totalWT = 0;

  sortByArrival(proc, n);

  while (completed < n) {
    int idx = -1, highestPriority = INT_MAX;

    for (int i = 0; i < n; i++) {
      if (proc[i].arrivalTime <= time && proc[i].completionTime == 0) {
        if (proc[i].priority < highestPriority) {
          highestPriority = proc[i].priority;
          idx = i;
        }
      }
    }

    if (idx == -1) {
      time++;
    } else {
      proc[idx].completionTime = time + proc[idx].burstTime;
      proc[idx].turnaroundTime =
          proc[idx].completionTime - proc[idx].arrivalTime;
      proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
      proc[idx].responseTime = proc[idx].waitingTime;

      totalTAT += proc[idx].turnaroundTime;
      totalWT += proc[idx].waitingTime;
      time = proc[idx].completionTime;
      completed++;
    }
  }

  printf("\nNon-Preemptive Priority Scheduling:\n");
  printf("PID\tAT\tBT\tP\tCT\tTAT\tWT\tRT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrivalTime,
           proc[i].burstTime, proc[i].priority, proc[i].completionTime,
           proc[i].turnaroundTime, proc[i].waitingTime, proc[i].responseTime);
  }

  printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
  printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
}

void prioritySchedulingPreemptive(struct Process proc[], int n) {
  int remainingTime[n], completed = 0, time = 0, shortest = -1;
  float totalTAT = 0, totalWT = 0;

  for (int i = 0; i < n; i++) {
    remainingTime[i] = proc[i].burstTime;
  }

  while (completed < n) {
    int highestPriority = INT_MAX;
    shortest = -1;

    for (int i = 0; i < n; i++) {
      if (proc[i].arrivalTime <= time && remainingTime[i] > 0) {
        if (proc[i].priority < highestPriority) {
          highestPriority = proc[i].priority;
          shortest = i;
        }
      }
    }

    if (shortest == -1) {
      time++;
    } else {
      if (remainingTime[shortest] == proc[shortest].burstTime) {
        proc[shortest].responseTime = time - proc[shortest].arrivalTime;
      }

      remainingTime[shortest]--;
      time++;

      if (remainingTime[shortest] == 0) {
        completed++;
        proc[shortest].completionTime = time;
        proc[shortest].turnaroundTime =
            proc[shortest].completionTime - proc[shortest].arrivalTime;
        proc[shortest].waitingTime =
            proc[shortest].turnaroundTime - proc[shortest].burstTime;

        totalTAT += proc[shortest].turnaroundTime;
        totalWT += proc[shortest].waitingTime;
      }
    }
  }

  printf("\nPreemptive Priority Scheduling:\n");
  printf("PID\tAT\tBT\tP\tCT\tTAT\tWT\tRT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrivalTime,
           proc[i].burstTime, proc[i].priority, proc[i].completionTime,
           proc[i].turnaroundTime, proc[i].waitingTime, proc[i].responseTime);
  }

  printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
  printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
}

int main() {
  int n, choice;

  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct Process proc[n];

  printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
  for (int i = 0; i < n; i++) {
    proc[i].id = i + 1;
    printf("Process %d - Arrival Time: ", i + 1);
    scanf("%d", &proc[i].arrivalTime);
    printf("Process %d - Burst Time: ", i + 1);
    scanf("%d", &proc[i].burstTime);
    printf("Process %d - Priority: ", i + 1);
    scanf("%d", &proc[i].priority);
  }

  printf("\nChoose Scheduling Type:\n1. Non-Preemptive\n2. Preemptive\nEnter "
         "choice: ");
  scanf("%d", &choice);

  if (choice == 1) {
    prioritySchedulingNonPreemptive(proc, n);
  } else if (choice == 2) {
    prioritySchedulingPreemptive(proc, n);
  } else {
    printf("Invalid choice!\n");
  }

  return 0;
}