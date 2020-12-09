#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
    char data[100];
    struct stack *next;
} Stack;

int isEmpty(Stack *stack) {
    return stack != NULL;
}

void push(Stack **stack, char *data) {

    Stack *temp;
    temp = (Stack *) malloc(sizeof(Stack));
    strcpy(temp->data, data);
    temp->next = *stack;
    *stack = temp;

}

char *pop(Stack **stack) {
    Stack *temp;
    if (isEmpty(*stack)) {
        temp = *stack;
        *stack = temp->next;
        return temp->data;
    }
    return "";
}


int isOperator(char c) {
    switch (c) {
        case '*':
        case '/':
        case '+':
        case '-':
        case '^':
            return 1;
        default:
            return 0;
    }

}

char *convert(char expression[]) {
    char *a, *b;
    char temp[100];
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->next = NULL;
    stack->data[0] = '\0';

    for (int i = (int)strlen(expression) - 1; i >= 0; i--) {
        if (isOperator(expression[i])) {
            a = pop(&stack);
            b = pop(&stack);
            temp[0] = '(';
            temp[1] = '\0';
            if (a[0]) {
                strncat(temp, a, strlen(a));
            }
            strncat(temp, &expression[i], 1);
            if (b[0]) {
                strncat(temp, b, strlen(b));
            }
            strncat(temp, ")", 1);
            strncat(temp, "\0", 1);

            push(&stack, temp);
        } else {
            temp[0] = expression[i];
            temp[1] = '\0';
            push(&stack, temp);
        }
    }
    return stack->data;
}

int main() {

    char exp[100];
    printf("Enter Prefix expression: ");
    scanf("%s", exp);
    printf("Infix: %s", convert(exp));
    fflush(stdin);
    getchar();

}
