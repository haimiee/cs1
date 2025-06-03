#include <stdio.h>

#define MAX_STUDENTS 100

struct student {
    char firstName[21];  // 20 chars max + '\0'
    char lastName[21];
    int ID;
    float GPA;
};

typedef struct student student_t;

void printStudent(student_t s) {
    printf("[%d, %s %s, GPA: %.2f]\n", s.ID, s.firstName, s.lastName, s.GPA);
}

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
    char filename[31];  // max filename length (including extension)

    printf("Enter file name to process: ");
    scanf("%s", filename);

    FILE *inp = fopen(filename, "r");
    if (!inp) {
        printf("Error: File does not exist.\n");
        return 1;
    }

    student_t students[MAX_STUDENTS];
    
    int count = 0;

    // Read each student (4 lines per student)
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

    fclose(inp);

int search;
printf("Enter a student ID to search or -1 to quit: ");
scanf("%d", &search);

while (search != -1) {
    searchID(search, students, count);
    printf("Enter a student ID to search or -1 to quit: ");
    scanf("%d", &search);
}

    // // Print all students to verify
    // for (int i = 0; i < count; i++) {
    //     printStudent(students[i]);
    // }
}
