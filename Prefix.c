#include <stdio.h>
#include <ctype.h> // For isdigit
#include <stdlib.h> // For exit()
#include <math.h>   // For pow()

#define MAX_SIZE 100 // Maximum stack size

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

// Initialize the stack
void initialize(Stack *s) {
    s->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if the stack is full
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Push an item onto the stack
void push(Stack *s, int item) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->arr[++(s->top)] = item;
}

// Pop an item from the stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->arr[(s->top)--];
}

// Function to perform arithmetic operations
int performOperation(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        case '^': return pow(operand1, operand2); // Using pow function for exponentiation
        default:
            printf("Invalid operator encountered: %c\n", operator);
            exit(1);
    }
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* postfix) {
    Stack s;
    initialize(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        // If the character is an operand (digit), push it onto the stack
        if (isdigit(ch)) {
            push(&s, ch - '0'); // Convert char digit to int
        }
        // If the character is an operator, pop two operands and apply the operation
        else {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            int result = performOperation(ch, operand1, operand2);
            push(&s, result); // Push the result back to the stack
        }
    }

    // The final result will be the only item in the stack
    return pop(&s);
}

int main() {
    char postfix[MAX_SIZE];

    printf("Enter a postfix expression (using single-digit operands): ");
    scanf("%s", postfix);

    int result = evaluatePostfix(postfix);

    printf("The result of the postfix expression is: %d\n", result);

    return 0;
}
