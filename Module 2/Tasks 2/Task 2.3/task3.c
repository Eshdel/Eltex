#include <stdio.h>
#include <stdlib.h>


float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);

typedef float (*Operation)(float, float);

int main() {
    // Array of function pointers
    Operation operations[] = {add, subtract, multiply, divide};
    char *operationSymbols = "+-*/";
    int numOperations = sizeof(operations) / sizeof(operations[0]);

    char operation;
    float num1, num2, result;

    printf("Available operations:\n");
    printf("+ - Addition\n");
    printf("- - Subtraction\n");
    printf("* - Multiplication\n");
    printf("/ - Division\n");
    printf("q - Quit the program\n");

    while (1) {
        printf("Choose operation: ");
        scanf(" %c", &operation);

        if (operation == 'q')
            break;

        int i;
        for (i = 0; i < numOperations; ++i) {
            if (operation == operationSymbols[i])
                break;
        }

        if (i == numOperations) {
            printf("Invalid operation\n");
            continue;
        }

        printf("Enter two numbers: ");
        scanf("%f %f", &num1, &num2);

        result = operations[i](num1, num2);
        printf("Result: %.2f\n", result);
    }

    return 0;
}

float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if (b != 0)
        return a / b;
    else {
        printf("Error: division by zero\n");
        return 0;
    }
}