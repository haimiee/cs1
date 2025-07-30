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

// Function to add value to the rear of the queue
void enqueue(Queue* q, int value) {
    printf("Attempting to add %d to the queue\n", value);

    Node* new_node = malloc(sizeof(Node));     // 1. Allocate memory for new node
    if (!new_node) {
        printf("Malloc failed for new node.\n");
        return;
    }
    new_node->data = value;                    // 2. Assign value to new node
    new_node->next = NULL;                     // 3. Set next as NULL (new rear)

    if (q->rear == NULL) {                     // 4. If queue is empty
        q->front = q->rear = new_node;         //    Set both front and rear to new node
    } else {
        q->rear->next = new_node;              // 5. Link old rear to new node
        q->rear = new_node;                    // 6. Update rear to the new node
    }

    printf("%d added to the queue!\n", new_node->data);
}

// Function to remove value from the front of the queue
void dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty, cannot dequeue.\n");
        return;
    }

    printf("Attempting to dequeue %d\n", q->front->data);
    Node* temp = q->front;             // 1. Save current front node
    q->front = q->front->next;         // 2. Move front to the next node

    if (q->front == NULL) {            // 3. If queue is now empty
        q->rear = NULL;                //    Set rear to NULL as well
    }

    free(temp);                        // 4. Free memory of the old front node
}

void display_menu() {
    printf("\nChoose an option\n");
    printf("1) View queue\n2) Enqueue\n3) Dequeue\n4) Peek\n5) Exit");
}

void display_queue(Node *head) {
    if (!head) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Here's the queue!\n");
    Node *currPtr = head;

    printf("\n[Front] ");
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
        printf("\nEnter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                display_queue(q.front);
                break;
            case 2:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
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
