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

char peek(Stack *stack) {
    return (char)stack->data[stack->top];
}

int isOperand(char a) {
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9');
}

int precedence(char a) {

    switch (a) {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        case '^':
            return 3;
        default:
            return -1;
    }

}
void reverse(char *data) {

    unsigned len = strlen(data);
    char temp;

    for (int i = 0; i < len/2; i++){
        temp = data[i];
        data[i] = data[len - i -1];
        data[len - i -1] = temp;
    }

}
char *toPostfix(char *data) {

    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->max = strlen(data);
    stack->data = (int *) malloc(stack->max * sizeof(int));
    stack->top = -1;
    int i = 0, j = 0;

    for (; data[i]; i++) {

        if (isOperand(data[i])) {
            data[j++] = data[i];
        } else {
            switch (data[i]) {
                case '(':
                    push(stack, data[i]);
                    break;
                case ')':
                    while (!isEmpty(stack) && peek(stack) != '(') {
                        data[j++] = pop(stack);
                    }
                    pop(stack);
                    break;
                default:
                    while (!isEmpty(stack) && precedence(data[i]) <= precedence(peek(stack))) {
                        data[j++] = pop(stack);
                    }
                    push(stack, data[i]);
            }
        }
    }

    while (!isEmpty(stack)) {
        data[j++] = pop(stack);
    }
    data[j] = '\0';
    return data;
}
void convert(char *data) {

    unsigned len = strlen(data);
    char *prefix;
    reverse(data);

    for (int i = 0; i < len; i++) {
        if (data[i] == '(') {
            data[i] = ')';
            i++;
        } else if (data[i] == ')') {
            data[i] = '(';
            i++;
        }
    }
    prefix = toPostfix(data);
    reverse(prefix);
    printf("Prefix: %s", prefix);
}
int main() {
    char exp[100];
    printf("Enter Infix expression: ");
    scanf("%s", exp);
    convert(exp);
    fflush(stdin);
    getchar();
}
