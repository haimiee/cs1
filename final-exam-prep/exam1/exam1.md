## Strings
- The way you declare strings of characters matters in C. There are different ways to do it and they each come with their own reasons.

### Pointer to a string literal
```c
int main() {
    char* coolString = "heya";
    printf("%s\n", coolString);
    
    return 0;
}
```
```bash
heya
```
- Using