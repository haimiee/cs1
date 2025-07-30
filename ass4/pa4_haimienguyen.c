#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    char name[100];
    struct Task* next;
} Task;

typedef struct {
    Task* front;
    Task* rear;
} TaskQueue;

typedef struct {
    Task* top;
} TaskStack;

void unenqueue(TaskQueue* q); 
void undequeue(TaskQueue* q, const char* taskName); 

// Queue operations
void enqueue(TaskQueue* q, const char* taskName) {
    // Create a new task node
    Task* newTask = malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newTask->name, taskName);
    newTask->next = NULL;

    // If queue is empty, set both front and rear to task name
    if (q->rear == NULL) {
        q->front = q->rear = newTask;
    } else { // otherwise set the new task to be the next in queue (send to rear)
        q->rear->next = newTask;
        q->rear = newTask;
    }
}

void dequeue(TaskQueue* q) {
    if (q->front == NULL) { // If nothing to dequeue
        return;
    }   

    Task* temp = q->front; // Store pointer to the front task to free later
    q->front = q->front->next; // Move the front pointer to the next task in line

    // If queue becomes empty after removal, update rear to NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void displayQueue(const TaskQueue* q) { // Output as instructed: "[Front] queueItem1 -> queueItem2 -> … [Rear]"
    printf("[Front] ");
    Task* curr = q->front; // Variable to track current node as we traverse
    
    while (curr != NULL) { // While loop to print and traverse queue of tasks
        printf("%s", curr->name);
        if (curr->next != NULL) { // Print arrow only if we're not at the end
            printf(" -> ");
        }
        curr = curr->next; // Traverse by setting new current to next pointer
    }
    
    printf(" [Rear]\n");
}

// Stack operations
void push(TaskStack* s, const char* taskName) {
    Task* newTask = malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newTask->name, taskName); // Copy given task name into new task
    newTask->next = s->top; // Point new task's next to current top
    s->top = newTask; // Set top to new taskName because stack
}

char* pop(TaskStack* s) {
    if (s->top == NULL) {
        return NULL;  // Nothing to pop if stack is empty
    }

    Task* temp = s->top;  // Save reference to the top task
    s->top = s->top->next;  // Move top pointer to the next task

    // Allocate memory for the task name to return
    char* poppedName = malloc(strlen(temp->name) + 1);
    if (poppedName == NULL) {
        printf("Memory allocation failed!\n");
        free(temp);
        return NULL;
    }
    strcpy(poppedName, temp->name);  // Copy the task name

    free(temp);  // Free the old top!

    return poppedName;  // Return the popped task name
}
void displayStack(const TaskStack* s) {
    printf("[Top] ");
    Task* curr = s->top; // Start traversal from the top of the stack

    // Traverse through the stack until reaching the bottom (NULL)
    while (curr != NULL) {
        printf("%s", curr->name);
        if (curr->next != NULL) { // Print arrow only if we're not at the end
            printf(" -> ");
        }
        curr = curr->next; // Traverse by setting new current to next pointer
    }
    
    printf(" [Bottom]\n");
}

// Task manager operations
void addTask(TaskQueue* q, TaskStack* undoStack, const char* taskName) {
    enqueue(q, taskName);  // Add to queue

    char log[120] = "Add: ";  // Build action log with output as instructed
    strcat(log, taskName);

    push(undoStack, log);  // Adds to undo stack

    printf("Added task: %s\n", taskName);
}

void processTask(TaskQueue* q, TaskStack* undoStack) {
    if (q->front == NULL) return;

    char taskName[100];
    strcpy(taskName, q->front->name);

    dequeue(q);

    char log[120] = "Process: ";
    strcat(log, taskName);
    push(undoStack, log);

    printf("Processed task: %s\n", taskName);
}

void undo(TaskQueue* q, TaskStack* undoStack, TaskStack* redoStack) {
    char* action = pop(undoStack); // Pop most recent action from undo stack
    if (action == NULL) return; // nothing to undo so return

    char actionType[20], taskName[100]; // store action type (Add or Process) and task name
    sscanf(action, "%[^:]: %[^\n]", actionType, taskName); // split action by colon

    // If last action was Add, undo it by removing from rear
    if (strcmp(actionType, "Add") == 0) {
        unenqueue(q); // remove from rear of queue (cancel the Add action)

        // Log undo action to redo stack
        char redoLog[120] = "Unprocessed: ";
        strcat(redoLog, taskName);
        push(redoStack, redoLog);

        printf("Undo: Unprocessed task: %s\n", taskName);
    }
    // If last action was Process, undo it by re-adding to front
    else if (strcmp(actionType, "Process") == 0) {
        undequeue(q, taskName); // re-add task to front of queue (cancel the Process action)

        // Log undo action to redo stack
        char redoLog[120] = "Re-processed: ";
        strcat(redoLog, taskName);
        push(redoStack, redoLog);

        printf("Undo: Unprocessed task: %s\n", taskName);
    }

    free(action); // free memory after using popped action
}


void redo(TaskQueue* q, TaskStack* undoStack, TaskStack* redoStack) {
    char* action = pop(redoStack); // Pop most recent redo action
    if (action == NULL) return; // nothing to redo so return

    char actionType[30], taskName[100]; // store action type (Unprocessed or Re-processed) and task name
    sscanf(action, "%[^:]: %[^\n]", actionType, taskName); // split action by colon

    // If last undone action was Unprocessed, redo by adding back to front of queue
    if (strcmp(actionType, "Unprocessed") == 0) {
        undequeue(q, taskName); // re-add to front of queue (reverting undo of Add)

        // Log redo action back into undo stack
        char undoLog[120] = "Add: ";
        strcat(undoLog, taskName);
        push(undoStack, undoLog);

        printf("Redo: Re-processed task: %s\n", taskName);
    }
    // If last undone action was Re-processed, redo by removing again from queue
    else if (strcmp(actionType, "Re-processed") == 0) {
        dequeue(q); // remove from front of queue (reverting undo of Process)

        // Log redo action back into undo stack
        char undoLog[120] = "Process: ";
        strcat(undoLog, taskName);
        push(undoStack, undoLog);

        printf("Redo: Unprocessed task: %s\n", taskName);
    }

    free(action); // free memory after using popped action
}


// Helper functions

// Reverse enqueue (remove from rear)
void unenqueue(TaskQueue* q) {
    if (q->front == NULL) { // Empty queue, nothing to remove
        return; 
    }

    if (q->front == q->rear) {
        // Only one node in queue
        free(q->front);
        q->front = q->rear = NULL;
        return;
    }
    Task* curr = q->front;
    while (curr->next != q->rear) {
        curr = curr->next;
    }
    // Now curr points to the second last node
    free(q->rear);
    curr->next = NULL;
    q->rear = curr;
}

// Reverse dequeue (re-add to front)
void undequeue(TaskQueue* q, const char* taskName) {
    Task* newTask = malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newTask->name, taskName);
    newTask->next = q->front;
    q->front = newTask;
    if (q->rear == NULL) q->rear = newTask;
}


int main() {
    TaskQueue queue = {NULL, NULL};
    TaskStack undoStack = {NULL};
    TaskStack redoStack = {NULL};
    addTask(&queue, &undoStack, "Email Client");
    addTask(&queue, &undoStack, "Compile Report");
    displayQueue(&queue);
    displayStack(&undoStack);
    displayStack(&redoStack);
    processTask(&queue, &undoStack);
    displayQueue(&queue);
    displayStack(&undoStack);
    displayStack(&redoStack);
    undo(&queue, &undoStack, &redoStack);
    displayQueue(&queue);
    displayStack(&undoStack);
    displayStack(&redoStack);
    redo(&queue, &undoStack, &redoStack);
    displayQueue(&queue);
    displayStack(&undoStack);
    displayStack(&redoStack);
    return 0;
}
