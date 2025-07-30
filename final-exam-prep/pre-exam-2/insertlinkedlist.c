#include <stdio.h>
#include <stdlib.h> // <-- needed for malloc

typedef struct node {
    int data;
    struct node* next;
} Node;

void insert(Node* head, int value) {
    printf("Attempting to add %d\n", value);
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        printf("Malloc failed!");
        return;
    }
    new_node->data = value;
    new_node->next = NULL;

    Node *temp = head;
    while (temp->next != NULL) { // Traverse to end of list using while loop
        temp = temp->next; 
    }
    temp->next = new_node; // Now that temp is end of list, set the new last node to new node
    printf("Added %d successfully!\n", new_node->data);
}

void display(Node *head) {
    printf("Linked list: ");
    Node *currPtr = head;
    while (currPtr != NULL) {
        printf("%d", currPtr->data);
        if (currPtr->next != NULL) printf(" -> ");
        currPtr = currPtr->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = malloc(sizeof(Node));
    head->data = 1;
    head->next = NULL;
    display(head);
    insert(head, 2);
    display(head);
    insert(head, 4);
    display(head);

    free_list(head);
    return 0;
}