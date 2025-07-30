/******************************************************************************

Task 1: Write a function that takes a string as its input, creates a new 
smart_string struct, and stores a new copy of that string in the word field 
of the struct and the length of that string in the length member of the 
struct. The function should then return a pointer to that new smart_string 
struct. Use dynamic memory management as necessary. The function signature is:
      smart_string* create_smart_string(char *str)  
Task 2: Now write a function that takes a smart_string pointer 
(which might be NULL) as its only argument, frees all dynamically allocated 
memory associated with that struct, and returns NULL when it’s finished. 
This function's signature is: 
      smart_string* erase_smart_string(smart_string *s)

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct smart_string { 
    char *word; 
    int length; 
} smart_string; 

smart_string* create_smart_string(char *str) {
    smart_string* newString = malloc(sizeof(smart_string));
    if (newString == NULL) {
        return NULL;
    }

    int len = strlen(str);
    newString->word = malloc((len + 1) * sizeof(char)); // <-- // Good habit: multiply by sizeof(type) even if sizeof(char) == 1
    if (newString->word == NULL) { // Good practice to free struct if inner malloc fails
        free(newString);
        return NULL;
    }
    
    // If we were to copy str as is into newString, we can:
    // strcopy(newString->word, str); <--copies the string exactly

    // OR do it manually:
    // for (int i = 0; i < len + 1; i++) { <--does what strcopy does under the hood
    //     newString->word[i] = str[i];
    // }

    // Copy each character from str to newString->word, converting to uppercase
    for (int i = 0; i < len; i++) {
        newString->word[i] = toupper(str[i]);
    }
    newString->word[len] = '\0';
    newString->length = len;
    
    return newString;
}

smart_string* erase_smart_string(smart_string *s) {
    if (!s) {return NULL;}
    if (!s->word) {
        free(s);
        return NULL;
    }

    free(s->word); // Only need to free the string because it's a malloc'd pointer
    free(s); // Free the struct itself

    return NULL;
}

// original wrongful attempt at main
// int main() {
//     char* s = "haimie";
//     printf("the og smart string: %s", *s); 
//     char* smartString = create_smart_string(*s); // ❌ WRONG: Dereferencing a string (e.g. *s) 
                                                    //gives the first character, not the full string. 
                                                    //It’s like saying “give me the value at the 
                                                    //first address of the array,” which is just a char.
                                                    //If you pass that to printf with %s, you're giving 
                                                    //it a character, not a pointer to a null-terminated 
                                                    // string — so printf will be confused or crash, 
                                                    //because %s expects a char * (a string), not a char.
//     printf("the copied smart string: %s", smartString); // ❌ WRONG: because the function returns a smart_string "type"
//     erase_smart_string(*s); // ❌ WRONG: passing wrong type. should be smart_string stype
    
//     return 0;
// }

// Lesson learned: pay attention to what the function expects in its parameters 
int main() {
    char* s = "joewoAoh";
    printf("the og smart string: %s\n", s);
    smart_string* newStr = create_smart_string(s);
    printf("the copied smart string: %s", newStr->word);
    newStr = erase_smart_string(newStr);
    
    return 0;
}
