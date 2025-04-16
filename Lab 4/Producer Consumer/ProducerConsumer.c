#include <stdio.h>

int mutex = 1, full = 0, empty = 3, x = 0;

void wait(int *s) {
    --(*s);
}

void signal(int *s) {
    ++(*s);
}

void producer() {
    wait(&empty);
    wait(&mutex);
    x++;
    printf("The item produced is %d\n", x);
    signal(&mutex);
    signal(&full);
}

void consumer() {
    wait(&full);
    wait(&mutex);
    printf("Consumed item %d\n", x);
    x--;
    signal(&mutex);
    signal(&empty);
}

int main() {
    int choice;
    do {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if ((mutex == 1) && (empty != 0)) {
                    producer();
                } else {
                    printf("The buffer is full\n");
                }
                break;
            case 2:
                if ((mutex == 1) && (full != 0)) {
                    consumer();
                } else {
                    printf("The buffer is empty\n");
                }
                break;
            case 3:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);
    return 0;
}