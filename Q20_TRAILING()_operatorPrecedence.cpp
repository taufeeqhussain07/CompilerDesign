#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100

char stack[MAX_STACK_SIZE];
int top = -1;

void push(char c) {
    if (top < MAX_STACK_SIZE - 1) {
        stack[++top] = c;
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

int getPrecedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int main() {
    char input[100];
    printf("Enter an expression: ");
    scanf("%s", input);
    strcat(input, "$"); // Add end marker

    int i = 0;

    while (input[i] != '\0') {
        char token = input[i];

        if (token == '(') {
            push(token);
        } else if (token == ')') {
            while (stack[top] != '(') {
                printf("%c", pop());
            }
            pop(); // Pop '('
        } else if (strchr("+-*/", token) != NULL) {
            while (getPrecedence(stack[top]) >= getPrecedence(token)) {
                printf("%c", pop());
            }
            push(token);
        } else if (token == '$') {
            while (top >= 0) {
                printf("%c", pop());
            }
        } else {
            printf("%c", token);
        }
        i++;
    }

    return 0;
}


