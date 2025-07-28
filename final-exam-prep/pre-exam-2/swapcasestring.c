/*
Write a function called swap_case_string() that takes a char * string as input 
and returns a new string (heap-allocated) where each lowercase letter is 
converted to uppercase and each uppercase letter is converted to lowercase. 
Leave non-alphabetical characters unchanged.

Then write a main() that:
- Creates a string like "HeLLo, WoRLd123!"
- Calls swap_case_string()
- Prints the result
- Frees any memory used
*/

#include <stdio.h>    // For printf
#include <ctype.h>    // For toupper() and tolower()
#include <string.h>   // For strlen()
#include <stdlib.h>   // For malloc() and free()

typedef struct {
    char* name;
    int length;
} smart_string;

smart_string* swaparoo(char *str) {
    smart_string* customString = malloc(sizeof(smart_string));
    if (customString == NULL) {
        printf("ERROR: Malloc failed!");
        return NULL;
    }

    int len = strlen(str);
    customString->name = malloc((len + 1) * sizeof(char));
    if (customString->name == NULL) {
        printf("ERROR: Malloc for smart string name failed!");
        free(customString);
        return NULL;
    }

    for (int i = 0; i <= len; i++) {
        if (islower(str[i])) {
            customString->name[i] = toupper(str[i]);
        } else if (isupper(str[i])) {
            customString->name[i] = tolower(str[i]);
        } else {
            customString->name[i] = str[i];
        }
    }

    return customString;
}

smart_string* erase_smart_string(smart_string *s) {
    if (!s) {
        printf("No string to free!");
        return NULL;
    }
    if (!s->name) {
        printf("No string name to free!");
        free(s);
        return NULL;
    }

    free(s->name);
    free(s);
    printf("Success\n");
    return NULL;
}

int main() {
    char* name = "jOLLIbEE";
    printf("name before case swap: %s\n", name);
    smart_string* newStr = swaparoo(name);
    printf("name after case swap: %s\n", newStr->name);
    printf("Now attempting to free the malloc'd new string\n");
    newStr = erase_smart_string(newStr);

    return 0;
}