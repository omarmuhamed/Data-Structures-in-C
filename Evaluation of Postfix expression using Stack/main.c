#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
    int top;
    unsigned max;
    int *data;
} Stack;

int isEmpty(Stack *stack) {
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}

void push(Stack *stack, char data) {
    stack->data[++stack->top] = (int)data;
}

char pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return (char)stack->data[stack->top--];
    }
    return '.';
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int calculate(int op1, int op2, char operator) {
    int sum;
    switch (operator) {
        case '+':
            return op2 + op1;
        case '-':
            return op2 - op1;
        case '*':
            return op2 * op1;
        case '/':
            return op2 / op1;
        case '^':
            sum = op2;
            for (; op1 > 1;){
                sum *= op2;
                op1--;
            }
            return sum;
        default:
            return -1;
    }
}
int evaluate(char data[]) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    stack->max = strlen(data);
    stack->data = (int *)malloc(sizeof(int) * stack->max);

    int op1, op2;

    for (int i = 0; i < stack->max; i++) {
        if (isDigit(data[i])) {
            push(stack, data[i] - '0');
        } else {
            op1 = pop(stack);
            op2 = pop(stack);
            push(stack, calculate(op1, op2, data[i]));
        }
    }
    return pop(stack);
}

int main() {
    char exp[100];
    printf("Enter Postfix expression: ");
    scanf("%s", exp);
    printf("Result: %d", evaluate(exp));
    fflush(stdin);
    getchar();
}
