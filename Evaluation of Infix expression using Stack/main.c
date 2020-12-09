#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct stack{
    int top;
    int max;
    int *data;
} Stack;

int isEmpty(Stack *stack) {
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}

int isFull(Stack *stack) {
    if (stack->top >= stack->max - 1 ) {
        return 1;
    }
    return 0;
}

void push(Stack *stack, int data) {
    if (!isFull(stack)) {
        stack->data[++stack->top] = data;
    }
}

int pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return -1;
}

int peek(Stack *stack){
    if(!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return -1;
}

int precedence(char op){
    if(op == '+'||op == '-')
        return 1;
    if(op == '*'||op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

int applyOp(int a, int b, char op){
    int sum;

    switch(op){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            sum = a;
            for (; b > 1;){
                sum *= a;
                b--;
            }
            return sum;
        default:
            return -1;


    }
}

int evaluate(char data[]) {
    Stack *operations = (Stack *)malloc(sizeof(Stack));
    Stack *results = (Stack *)malloc(sizeof(Stack));
    operations->top = -1;
    results->top = -1;
    operations->max = 100;
    results->max = 100;
    results->data = (int *)malloc(100 * sizeof(int));
    operations->data = (int *)malloc(100 * sizeof(int));

    int val, val1, val2;
    char operation;

    for (int i = 0; i < strlen(data); i++){

        if (data[i] == ' ') {
            continue;
        } else if (data[i] == '(') {
            push(operations, data[i]);
        } else if (isdigit(data[i])) {
            val = 0;
            while (i < strlen(data) && isdigit(data[i])) {
                val = (val * 10) + (data[i] - '0');
                i++;
            }
            push(results, val);
            i--;
        } else if (data[i] == ')') {
            while(!isEmpty(operations) && peek(operations) != '(') {
                val2 = pop(results);
                val1 = pop(results);
                operation = (char)pop(operations);
                push(results, applyOp(val1, val2, operation));
            }
            if (!isEmpty(operations)) {
                pop(operations);
            }
        } else {
            while (!isEmpty(operations) && precedence((char)peek(operations)) >= precedence(data[i])) {
                val2 = pop(results);
                val1 = pop(results);
                operation = (char)pop(operations);
                push(results, applyOp(val1, val2, operation));
            }
            push(operations, data[i]);
        }
    }
    while (!isEmpty(operations)) {
        val2 = pop(results);
        val1 = pop(results);
        operation = (char)pop(operations);
        push(results, applyOp(val1, val2, operation));
    }
    return peek(results);
}
int main() {
    char exp[100];
    printf("Enter Infix expression: ");
    scanf("%s", exp);
    printf("Result: %d", evaluate(exp));
    fflush(stdin);
    getchar();
}
