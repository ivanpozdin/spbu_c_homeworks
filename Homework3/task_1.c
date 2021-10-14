#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printBinaryNumber(int number)
{
    printf("%i", number < 0);
    if (number < 0)
        for (int i = 31; i >= 0; i--)
            printf("%i", !((bool)(1<<i & number)));
    else
        for (int i = 31; i >= 0; i--)
            printf("%i", (bool)(1<<i & number));
}

int main()
{
    int a, b;
    printf("Enter two numbers: ");
    scanf("%i %i", &a, &b);
    printf("First number in binary form: ");
    printBinaryNumber(a);
    printf("\nSecond number in binary form: ");
    printBinaryNumber(b);
    printf("\nSum of the numbers in decimal form: %i, in binary form: ", a + b);
    printBinaryNumber(a + b);

    return 0;
}