## *Exam 1* Review - SI
<div align="center">
    <strong><span style="font-size: 20px; display: block;">C Review</span></strong>
    <h1> </h1>
</div>

### **Given the pointer manipulation code below:**
```c
int data[] = {4, 6, 8, 10};
int *p = data + 2;
```
- What value does *p hold? (What address is the pointer holding)
- What is the value of *(p-1)?

`data` alone holds the address of the array, which is a pointer to the first index data[0]

`*p = data + 2` means that `*p` is equal to the first index plus 2 over, aka `data[2]`, which is 8

```in technical terms, *p is equal to the address of 8, and when dereferenced, *p evaluates to 8```

```*(p-1) is pointing to one before the address of *p, so 6```

### **In what situation would there be an error for trying to strcpy(str2, str1);?**
```if you never allocated memory to the variables, in other words, str2 is not pointing to any location in the computer```