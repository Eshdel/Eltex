#include <stdio.h>

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

int main() {
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

        printf("Enter two numbers: ");
        scanf("%f %f", &num1, &num2);

        switch(operation) {
            case '+':
                result = add(num1, num2);
                break;
            case '-':
                result = subtract(num1, num2);
                break;
            case '*':
                result = multiply(num1, num2);
                break;
            case '/':
                result = divide(num1, num2);
                break;
            default:
                printf("Invalid operation\n");
                continue;
        }

        printf("Result: %.2f\n", result);
    }

    return 0;
}