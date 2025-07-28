## *Pre Exam 2*
<div align="center">
    <strong><span style="font-size: 20px; display: block;">C Review</span></strong>
    <h1> </h1>
</div>

### File Headers
| Header File       | Purpose                                                                 | Common Functions/Macros Used                      |
|-------------------|-------------------------------------------------------------------------|--------------------------------------------------|
| `<stdio.h>`       | Provides input/output functionality.                                    | `printf()`, `scanf()`, `puts()`, `gets()`, `fopen()` |
| `<string.h>`      | Contains string handling functions.                                     | `strlen()`, `strcpy()`, `strcmp()`, `strcat()`   |
| `<ctype.h>`       | Provides functions for character classification and conversion.         | `toupper()`, `tolower()`, `isalpha()`, `isdigit()` |
| `<stdlib.h>`      | Provides functions for memory allocation, process control, conversions. | `malloc()`, `free()`, `exit()`, `atoi()`, `rand()` |

### Data Type Sizes
| Data Type       | Description                     | Typical Size (bytes) | Notes                                  |
|------------------|---------------------------------|-----------------------|----------------------------------------|
| `char`           | Single character                | 1                     | Often used in strings                  |
| `int`            | Integer                         | 4                     | Most common integer type               |
| `float`          | Single-precision float          | 4                     | Basic real number                      |
| `double`         | Double-precision float          | 8                     | More accurate than float               |
| `void *`         | Generic pointer                 | 8                     | Points to any data type                |
| `char *`         | Pointer to char / string        | 8                     | Often used with strings                |
| `int *`          | Pointer to int                  | 8                     | Used for dynamic arrays                |

### C Pointer & Pointer Arithmetic

## What is a Pointer?
- A pointer is a variable that stores the **address** of another variable.
- Example: `char *p = "Hello";` → `p` points to the first character `'H'`.

## 📏 Pointer Size
- On a 64-bit system, all pointers (`char *`, `int *`, etc.) are **8 bytes**.
- They store a memory address.

## String Literal vs Array
| Code                         | Description                          |
|------------------------------|--------------------------------------|
| `char *p = "Hello";`         | Points to a read-only string literal |
| `char arr[] = "Hello";`      | Mutable array on the stack           |
| `sizeof(p)`                  | 8 (pointer only)                     |
| `sizeof(arr)`                | 6 (includes null terminator)         |

## Pointer Arithmetic
- Pointers can be incremented to access elements like arrays:
  ```c
  *(p + 0) == p[0] == 'H'
  *(p + 1) == p[1] == 'e'
