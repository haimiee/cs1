#include <stdio.h>
#include <stdlib.h>

// Function declarations
char* str_copy(const char* src);
// Dynamically allocates memory and returns a deep copy of the input string.
// The caller is responsible for freeing the returned memory.

char* str_concat(const char* s1, const char* s2);
// Dynamically allocates memory and returns a new string that is the
// concatenation of s1 followed by s2. The caller is responsible for freeing it.

int str_length(const char* s);
// Returns the number of characters in the string (excluding the null terminator).

int str_compare(const char* s1, const char* s2);
// Returns 0 if the strings are equal,
// A negative value if s1 < s2,
// A positive value if s1 > s2 (lexicographically).

void str_free(char* s);
// Frees dynamically allocated memory created by your custom string functions.

// Function to return string length using pointer arithmetic
int str_length(const char* s) { // s = "Hello\0"
    const char *start = s; // Mark start of string
    while (*s != '\0') {
        s++;  // Walk the memory until null terminator '\0'
    }
    return s - start;  // Return difference between last string's address and starting char's address
}

// Function to copy string in a malloc'ed space
char* str_copy(const char* src) {
    int length = str_length(src);
    // printf("Length of original string: %d\n", length);

    // If statement if string is empty
    if (length == 0) {
        char* copy = malloc(1);  // Only need space for '\0'
        if (copy == NULL) {
            printf("Malloc failed.\n");
            return NULL;
        }
        copy[0] = '\0';
        return copy;
    }

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
    
    // printf("Length between the two strings: %d\n", total_len); // Works!

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