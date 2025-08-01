#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct stack {
    Node* top;
} Stack;

// Function to add value to the top of the stack
void push(Stack* stack, int value) {
    printf("Attempting to add %d\n", value);

    Node* new_node = malloc(sizeof(Node));         // 1. Allocate memory for new node
    if (!new_node) {                               // 2. Return if malloc fails
        printf("Malloc failed for new node.\n");
        return;
    }
    new_node->data = value;                        // 3. Assign value to it
    new_node->next = stack->top;                   // 4. Link to the old top
    stack->top = new_node;                         // 5. Update stack's top to the new node

    printf("%d is now the top!\n", new_node->data);
}

// Function to remove the top value from the stack
void pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is already empty!\n");
        return;
    }

    Node* temp = stack->top;           // 1. Save the current top node
    printf("Popping: %d\n", temp->data);
    stack->top = stack->top->next;     // 2. Move top to the next node
    free(temp);                        // 3. Free memory of the removed node
} 

void peek(Stack* stack) {
    printf("Attempting to peek at the stack...\n");
    if (!stack->top) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top of the stack is %d!\n", stack->top->data);
}

void display_stack(Node* top) {
    printf("[Top] ");
    if (!top) {
        printf(" [End]\n");
        return;
    }

    Node* curr = top;
    while (curr) {
        printf("%d", curr->data);
        if (curr->next) printf(" -> ");
        curr = curr->next;
    }
    printf(" [End]\n");
}

int main() {
    Stack* s = malloc(sizeof(Stack));
    s->top = NULL;
    push(s, 2);
    display_stack(s->top); // ✅ pass the top node
    push(s, 4);
    display_stack(s->top);
    push(s, 6);
    display_stack(s->top); 
    peek(s);
    pop(s);
    display_stack(s->top);
    peek(s);
    pop(s);
    pop(s);
    pop(s);
    peek(s);
    free(s);
    return 0;
}