#include <stdio.h>

#define MAX_STUDENTS 100 // Assuming no more than 100 records

struct student {
    char firstName[21];  // 20 chars max + \0
    char lastName[21];
    int ID;
    float GPA;
};

typedef struct student student_t;

// Print student's details in formatted way
void printStudent(student_t s) {
    printf("[%d, %s %s, GPA: %.2f]\n", s.ID, s.firstName, s.lastName, s.GPA);
}

// Perform binary search to find student by ID
void searchID(int id, student_t students[], int count) {
    int low = 0, high = count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].ID == id) {
            printStudent(students[mid]);
            return;
        } else if (students[mid].ID < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("This ID is not in the records.\n");
}

int main() {
    char filename[31];  // Max filename length (including extension) + \0

    printf("Enter file name to process: ");
    scanf("%s", filename);

    // Try to open the file for reading
    FILE *inp = fopen(filename, "r");
    if (!inp) {
        printf("Error: File does not exist.\n");
        return 1;
    }

    student_t students[MAX_STUDENTS]; // Array to hold student records
    
    int count = 0; // Count how many students read

    // Read data for each student (4 lines per student)
    while (fscanf(inp, "%d", &students[count].ID) != EOF) {
        fscanf(inp, "%20s", students[count].firstName);
        fscanf(inp, "%20s", students[count].lastName);
        fscanf(inp, "%f", &students[count].GPA);
        
        // Check for increasing ID order
        if (count > 0 && students[count].ID <= students[count - 1].ID) {
            printf("Error: Student IDs not in increasing order.\n");
            fclose(inp);
            return 1;
        }        
        
        count++;
    }

    fclose(inp); // Close file after reading all records

    // Allows user to search for student IDs until enter -1
    int search;
    printf("Enter a student ID to search or -1 to quit: ");
    scanf("%d", &search);

    while (search != -1) {
        searchID(search, students, count);
        printf("Enter a student ID to search or -1 to quit: ");
        scanf("%d", &search);
    }

}
