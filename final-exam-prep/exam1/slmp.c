#include <stdio.h>
// This is an algorithm we implemented to
// solve the sorted list matching problem
// for integer arrays
// array 1 & 2 are SORTED arrays of integers,
// len1 length of array1
// len2 length of array2
void printCommonNumbers(int array1[], int len1, int array2[], int len2) {
    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (array1[i] == array2[j]) {
            printf("%d is common\n", array1[i]);
            i++;
            j++;
    }
    else if (array1[i] < array2[j])
        i++;
    else
        j++;
    }
}
int main() {
    int exampleArray1[] = {5, 7, 20, 22, 25};
    int exampleArray2[] = {2, 3, 5, 21, 25};

    printCommonNumbers(exampleArray1, 5, exampleArray2, 5);
    return 0;
}
