#include <stdio.h>
#include <stdlib.h>

// Function declarations
char* str_copy(const char* src);
char* str_concat(const char* s1, const char* s2);
int str_length(const char* s);
int str_compare(const char* s1, const char* s2);
void str_free(char* s);

// Function to return string length using pointer arithmetic
int str_length(const char* s) {
    const char *start = s; // Mark start of string
    while (*s != '\0') {
        s++;  // Walk the memory until null terminator '\0'
    }
    return s - start;  // Return difference between last string's address and starting char's address
}

// Function to copy string in a malloc'ed space
char* str_copy(const char* src) {
    int length = str_length(src);

    // Allocate memory for new copied string
    char *copy = malloc((length + 1) * sizeof(char));
    if (copy == NULL) {
        printf("Malloc failed.\n");
        return NULL;
    }

    // For loop to copy over original string into copy
    for (int i = 0; i <= length; i++) {
        copy[i] = src[i];
    }

    return copy;
}

// Concatonate two given strings
char* str_concat(const char* s1, const char* s2) {
    int s1_len = str_length(s1);
    int s2_len = str_length(s2);
    int total_len = s1_len + s2_len;

    // Allocate memory for new copied string
    char *new_string = malloc((total_len + 1) * sizeof(char));
    if (new_string == NULL) {
        printf("Malloc failed.\n");
        return NULL;
    }

    // Copy first string into new string
    for (int i = 0; i < s1_len; i++) {
        new_string[i] = s1[i];
    }

    // Copy second string into new string starting after first string
    for (int j = 0; j <= s2_len; j++) {
        new_string[s1_len + j] = s2[j];
    }

    return new_string;
}

// Compare strings based on ASCII values
int str_compare(const char* s1, const char* s2) {
    // While string 1 AND string 2 point to a valid character
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            // Once unmatched char return difference, either pos or neg
            return *s1 - *s2;
        }
        // Walk through memories of both strings
        s1++;
        s2++;
    }
    
    // Return difference anyway
    return *s1 - *s2;
}

// Function to free dynamically allocated memory created by string functions
void str_free(char* s) {
    free(s);
}

int main() {
    // Test str_length
    const char *original = "Hello";
    printf("Length of '%s' is %d\n", original, str_length(original));

    // Test str_copy
    char *copy = str_copy(original);
    printf("Copy of '%s' is '%s'\n", original, copy);

    // Test str_concat
    const char *add_on = " World!";
    char *combined = str_concat(original, add_on);
    printf("Concatenation of '%s' and '%s' is '%s'\n", original, add_on, combined);

    // Test str_compare
    const char *a = "apple";
    const char *b = "banana";
    const char *c = "apple";
    printf("Compare '%s' with '%s': %d\n", a, b, str_compare(a, b)); // should be negative
    printf("Compare '%s' with '%s': %d\n", a, c, str_compare(a, c)); // should be 0
    printf("Compare '%s' with '%s': %d\n", b, a, str_compare(b, a)); // should be positive

    // Free allocated memory
    str_free(copy);
    str_free(combined);

    return 0;
}