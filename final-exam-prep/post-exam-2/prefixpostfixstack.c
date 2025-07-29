#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int value) {
    s->items[++(s->top)] = value;
}

int pop(Stack* s) {
    return s->items[(s->top)--];
}

int evaluate_postfix(const char* expr) {
    Stack s;
    init(&s);

    char token[10];
    int i = 0;

    while (*expr) {
        if (isdigit(*expr)) {
            token[i++] = *expr;
        } else if (*expr == ' ') {
            if (i > 0) {
                token[i] = '\0';
                push(&s, atoi(token));
                i = 0;
            }
        } else if (*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/') {
            int right = pop(&s);
            int left = pop(&s);
            switch (*expr) {
                case '+': push(&s, left + right); break;
                case '-': push(&s, left - right); break;
                case '*': push(&s, left * right); break;
                case '/': push(&s, left / right); break;
            }
        }
        expr++;
    }

    return pop(&s);
}

int main() {
    const char* expr = "3 4 2 * +";
    printf("Result: %d\n", evaluate_postfix(expr));
    return 0;
}
