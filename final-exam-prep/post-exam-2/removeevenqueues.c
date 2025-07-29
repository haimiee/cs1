#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

void display_menu() {
    printf("Choose an option\n");
    printf("1) View queue\n2) Enqueue\n3) Dequeue\n4) Peekn\n5) Exit");
}

void display_queue(Node *head) {
    if (!head) {
        printf("Queue is empty!");
        return;
    }
    printf("Here's the queue!");
    Node *currPtr = head;

    printf("[Front] ");
    while (currPtr != NULL) {
        printf("%d", currPtr->data);
        if (currPtr->next != NULL) printf(" -> ");
        currPtr = currPtr->next;
    }
    printf(" [Rear]\n");
}

void free_list(Node *front) {
    Node *temp;
    while (front != NULL) {
        temp = front;
        front = front->next;
        free(temp);
    }
}

int main() {
    printf("Welcome to Queue Program!\n");
    Queue q;
    q.front = q.rear = NULL;

    int userChoice;
    int value;

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                display_queue(&q);
                break;
            // case 2:
            //     printf("Enter value to enqueue: ");
            //     scanf("%d", &value);
            //     enqueue(&q, value);
            //     break;
            // case 3:
            //     dequeue(&q);
            //     break;
            // case 4:
            //     peek(&q);
            //     break;
            case 5:
                free_list(q.front);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
