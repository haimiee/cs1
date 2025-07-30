## *Pre Exam 2*
<div align="center">
    <strong><span style="font-size: 20px; display: block;">C Review</span></strong>
    <h1> </h1>
</div>

# File Headers
| Header File       | Purpose                                                                 | Common Functions/Macros Used                      |
|-------------------|-------------------------------------------------------------------------|--------------------------------------------------|
| `<stdio.h>`       | Provides input/output functionality.                                    | `printf()`, `scanf()`, `puts()`, `gets()`, `fopen()` |
| `<string.h>`      | Contains string handling functions.                                     | `strlen()`, `strcpy()`, `strcmp()`, `strcat()`   |
| `<ctype.h>`       | Provides functions for character classification and conversion.         | `toupper()`, `tolower()`, `isalpha()`, `isdigit()` |
| `<stdlib.h>`      | Provides functions for memory allocation, process control, conversions. | `malloc()`, `free()`, `exit()`, `atoi()`, `rand()` |

# Data Type Sizes
| Data Type       | Description                     | Typical Size (bytes) | Notes                                  |
|------------------|---------------------------------|-----------------------|----------------------------------------|
| `char`           | Single character                | 1                     | Often used in strings                  |
| `int`            | Integer                         | 4                     | Most common integer type               |
| `float`          | Single-precision float          | 4                     | Basic real number                      |
| `double`         | Double-precision float          | 8                     | More accurate than float               |
| `void *`         | Generic pointer                 | 8                     | Points to any data type                |
| `char *`         | Pointer to char / string        | 8                     | Often used with strings                |
| `int *`          | Pointer to int                  | 8                     | Used for dynamic arrays                |

# C Pointer & Pointer Arithmetic

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

# Pointer Arithmetic
- Pointers can be incremented to access elements like arrays:
  ```c
  *(p + 0) == p[0] == 'H'
  *(p + 1) == p[1] == 'e'

# Linked List vs Array

## 📦 What is a Linked List?

A **linked list** is a dynamic data structure made of **nodes**, where each node stores:
1. A **value**
2. A **pointer** to the next node in the list

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;
```
A visual example (where o- represents a pointer):
```bash 
[3 | o-] -> [7 | o-] -> [2 | o-] -> [9 | NULL]
```

## What is `struct` for?

In C, a `struct` lets you group variables together into a **single custom data type**.

For linked lists, we use a `struct` to define each **node**, so that every node contains:
- A value (like `int data`)
- A pointer to the next node (`struct Node *next`)

Example:

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;
``` 
## Linked Lists
Advantages:
- Dynamically sized — grows as needed
- Fast insertions/deletions at the beginning or middle
- No shifting required (unlike arrays)

Disadvantages:
- Slower element access — must traverse (O(n))
- More memory usage (each node holds a pointer)
- Pointers can be tricky to manage/debug

Why Not Just Use an Array?
Arrays are great if:
- You need random access (like arr[42])
- You don't expect to insert/delete elements often

Arrays are limiting if:
- You frequently insert/delete in the middle
- You don’t know how large the array should be in advance

### Key Comparison Table: Array vs Linked List

| Feature                  | Array                          | Linked List                       |
|--------------------------|--------------------------------|-----------------------------------|
| **Random Access**        | ✅ O(1)                         | ❌ O(n) (must traverse nodes)     |
| **Insert/Delete Front**  | ❌ O(n) (requires shifting)     | ✅ O(1) if using head insert      |
| **Insert/Delete Middle** | ❌ O(n)                         | ✅ O(1) (if pointer to node known)|
| **Insert/Delete End**    | ✅ O(1) (if space available)    | ✅ O(1) (if tail pointer exists)  |
| **Dynamic Size**         | ❌ Fixed size unless resized    | ✅ Fully dynamic (via malloc)     |
| **Memory Overhead**      | Low (only data stored)         | Higher (stores data + pointer)   |
| **Ease of Use**          | Easier to implement and debug  | More complex pointer logic        |

# Memory Layout in C Programs
| **Memory Region**  | **Location (High → Low)** | **What’s Stored**                                            | **Access Type**     | **Example**                                   |
| ------------------ | ------------------------- | ------------------------------------------------------------ | ------------------- | --------------------------------------------- |
| **Stack**          | High                      | Local variables, function parameters, return addresses       | Read/Write          | `int x = 5;` inside a function                |
| **Heap**           | Grows up                  | Dynamically allocated memory (`malloc`, `calloc`, `realloc`) | Read/Write          | `char *s = malloc(10);`                       |
| **BSS Segment**    | Below heap                | Uninitialized global/static variables                        | Read/Write          | `static int count;`                           |
| **Data Segment**   | Below BSS                 | Initialized global/static variables                          | Read/Write          | `int count = 5;`                              |
| **Text Segment**   | Lowest                    | Actual program instructions (compiled machine code)          | Read-Only (usually) | The compiled `main()` function code           |
| **Read-Only Data** | Adjacent to Text segment  | Constants and string literals                                | Read-Only           | `char *msg = "hello";` → `"hello"` lives here |

- String literals are stored in the Read-Only Data section. Modifying them directly causes segmentation faults.

- The heap and stack grow toward each other: if they collide (due to infinite recursion or memory leaks), the program crashes.

- Heap memory must be freed manually using free(). Stack memory is cleaned up automatically on function return.

- Global/static variables exist throughout the entire program runtime; locals on the stack do not.