#include <stdio.h>
#define MAX_NAME_LEN 100

typedef struct hub {
    char name[MAX_NAME_LEN]; // city or location name
    int distance; // distance from previous hub
    int hour; // simplified timestamp (0–23)
    struct hub* next;
} Hub;

// int is_empty(struct hub* head) {

// }


void insert_at_head(Hub** head, const char* name, int distance, int hour) {
    // Allocate memory for a new Hub node
    Hub *newHub = malloc(sizeof(Hub));
    
    strcpy(newHub->name, name);
    newHub->distance = distance;
    newHub->hour = hour;

    newHub->name = head;
    // Fill in the data:
        // Copy the name string
        // Set the distance    
        // Set the hour
    // Link the new node to the current head
    // Update the head to point to the new node

}

// void insert_at_tail(Hub** head, const char* name, int distance, int hour) {

// }

// void print_chain(Hub* head) {

// }

// int total_distance(Hub* head) {

// }

// void print_chain_reverse(Hub* head) {

// }

// void display_bottleneck(Hub* head) {

// }

// Hub search_hub(Hub* head, const char* keyword) {

// }

// void remove_first_match(Hub** head, const char* keyword) {

// }

// void deleteList(Hub *head) {
//     Hub *temp;
//     while (head != NULL) {
//         temp = head;
//         head = head->next;
//         free(temp);
//     }
// }

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
    // display_bottleneck(chain);
    
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