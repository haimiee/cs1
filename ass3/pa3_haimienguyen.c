#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct hub {
    char name[MAX_NAME_LEN]; // city or location name
    int distance; // distance from previous hub
    int hour; // simplified timestamp (0–23)
    struct hub* next;
} Hub;

// Function to check if list is empty
int is_empty(struct hub* head) {
    if (head == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Function to add a new hub at the beginning
void insert_at_head(Hub** head, const char* name, int distance, int hour) {
    // Allocate memory for a new Hub node
    Hub *newHub = malloc(sizeof(Hub));
    if (newHub == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
    // Save new hub's name, distance, and hour
    strcpy(newHub->name, name);
    newHub->distance = distance;
    newHub->hour = hour;

    newHub->next = *head; // Link new node to current head
    *head = newHub; // Update head to point to new node
}

// Recursive function to add a new hub at the end
void insert_at_tail(Hub** head, const char* name, int distance, int hour) {
    if (*head == NULL) {
        // We're at the tail (or list is empty) — create the node here
        Hub* newHub = malloc(sizeof(Hub));
        if (!newHub) return;

        // Save new hub's name, distance, and hour
        strcpy(newHub->name, name);
        newHub->distance = distance;
        newHub->hour = hour;
        newHub->next = NULL;

        *head = newHub;  // Attach to current NULL slot
        return;
    }

    // Otherwise, recurse deeper
    insert_at_tail(&((*head)->next), name, distance, hour);
}

// Function to print the hubs in order iteratively
void print_chain(Hub* head) {
    if (head == NULL) {
        printf("List is empty!");
        return;
    }

    Hub *temp = head;
    while (temp != NULL) {
        printf("%s - %d km, %dh\n", temp->name, temp->distance, temp->hour);
        temp = temp->next;
    }
}

// Iterative function to print the total distance of the delivery chain
int total_distance(Hub* head) {
    if (head == NULL) {
        printf("List is empty!");
        return 0;
    }

    int distance = 0;
    Hub *temp = head;
    while (temp != NULL) {
        distance += temp->distance;
        temp = temp->next;
    }

    return distance;
}

// Recursive function to print the delivery chain in reverse order
void print_chain_reverse(Hub* head) {
    if (head == NULL)
        return;

    print_chain_reverse(head->next);  // Recurse first
    printf("%s - %d km, %dh\n", head->name, head->distance, head->hour);
  // Then print after so it prints when going back up call stack
}

// Function to find max hours spent between two consecutive hubs in the chain and print in special format
void display_bottleneck(Hub* head) {
    // Check if linked list is empty or only 1 node
    if (head == NULL || head->next == NULL) {
        return;
    }

    // Save current head and next into their own variables to be updated later
    Hub* origin = head;
    Hub* destination = head->next;

    // Subtract next node's hour from current node's hour and save
    int maxGap = destination->hour - origin->hour;
    Hub* maxOrigin = origin; // Save this current max's current node into variable
    Hub* maxDest = destination; // Save this current max's next node into variable

    // While loop to update above if new max found
    while (destination != NULL) {
        int gap = destination->hour - origin->hour; // Variable to save current gap
        // If the gap is greater than maxGap, update gap, origin, and destination
        if (gap > maxGap) {
            maxGap = gap;
            maxOrigin = origin;
            maxDest = destination;
        }
        origin = destination;
        destination = destination->next;
    }

    printf("Bottleneck: %s → %s, Time spent: %d hours\n", maxOrigin->name, maxDest->name, maxGap);
}

// Function to search matching string in linked list's names
Hub search_hub(Hub* head, const char* keyword) {
    // Temp variable to store the full name
    Hub* temp = head;
    while (temp != NULL) {
        if (strstr(temp->name, keyword) != NULL) { // Use string library's strstr func to check for matching
            return *temp;  // Return a copy of the matching hub
        }
        temp = temp->next; // Traverse list if no match
    }

    // If no match found, return a dummy hub
    Hub notFound;
    strcpy(notFound.name, "None");
    notFound.distance = -1;
    notFound.hour = -1;
    notFound.next = NULL;

    return notFound;
    // Return a copy so no need to free allocated memory
}

// Function to search matching string then remove that node
void remove_first_match(Hub** head, const char* keyword) {
    // Check if linked list is empty
    if (*head == NULL) {
        printf("List is empty!");
        return;
    }

    // Variables to save the node to delete later and its previous node
    Hub* curr = *head;
    Hub* prev = NULL;

    // While loop to look for matching keyword using strstr 
    // then update previous pointer to current node's next pointer
    while (curr != NULL) {
        if (strstr(curr->name, keyword)) {
            // Match found
            if (prev == NULL) {
                // Match is at the head
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr); // Free the memory to the match's node
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Frees all nodes in the linked list to prevent memory leaks
void deleteList(Hub *head) {
    Hub *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    printf("=== ParcelTrack Delivery Chain Test ===\n\n");
    Hub* chain = NULL;

    // Test insert_at_head and insert_at_tail
    insert_at_head(&chain, "Orlando", 0, 9);
    insert_at_tail(&chain, "Atlanta", 400, 14);
    insert_at_tail(&chain, "Charlotte", 350, 17);
    
    printf("Delivery chain:\n");
    print_chain(chain);
    printf("\n");
 
    // Test total_distance
    int total = total_distance(chain);
    printf("Total distance: %d km\n\n", total);
 
    // Test display_bottleneck
    // Uncomment the line below if bonus attempted
    display_bottleneck(chain);
    
    // Test search_hub
    Hub found = search_hub(chain, "lanta");
    if (strcmp(found.name,"None")) {
        printf("Search result: Found ");
        printf("\"{%s, %d, %d}\"\n\n", found.name, found.distance, found.hour);
    } else
        printf("Search result: No match found\n\n");
 
    // Test print_chain_reverse
    printf("Reverse delivery chain:\n");
    print_chain_reverse(chain);
    printf("\n");

    // Test remove_first_match
    remove_first_match(&chain, "lanta");
    printf("After removing first match for \"lanta\":\n");
    print_chain(chain);
    printf("\n");
    deleteList(chain);
    chain = NULL;
    return 0;
}