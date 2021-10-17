#include <stdbool.h>
#include <stdio.h>

void printBinaryNumber(bool* binaryNumber)
{
    for (int i = 31; i >= 0; i--)
        printf("%d", binaryNumber[i]);
}
void convertFromDecimalToBinary(bool* binaryNumber, int decimalNumber)
{
    for (int i = 31; i >= 0; i--)
        binaryNumber[i] = (bool)(1 << i & decimalNumber);
}

void addTwoBinaryNumbers(const bool* number1, const bool* number2, bool* result)
{
    bool inMind = 0;
    for (int i = 0; i < 32; i++) {
        if (inMind) {
            if (number1[i] && number2[i])
                result[i] = 1;
            else if (number1[i] ^ number2[i])
                result[i] = 0;
            else {
                result[i] = 1;
                inMind = 0;
            }
        } else {
            if (number1[i] && number2[i]) {
                result[i] = 0;
                inMind = 1;
            } else if (number1[i] ^ number2[i])
                result[i] = 1;
            else
                result[i] = 0;
        }
    }
}

void productTwoNumbers(const bool* number1, const bool* number2, bool* result)
{
    for (int i = 0; i < 32; i++) {
        bool resultOfPrimaryProduct[32];
        for (int k = 0; k < 32; k++)
            resultOfPrimaryProduct[k] = 0;

        for (int j = 0; j + i < 32; j++)
            resultOfPrimaryProduct[j + i] = number1[j] && number2[i];

        addTwoBinaryNumbers(resultOfPrimaryProduct, result, result);
    }
}

int main()
{
    int a, b;
    printf("Enter two integer numbers: ");
    scanf("%i %i", &a, &b);
    bool binaryA[32], binaryB[32], binaryProduct[32];
    for (int k = 0; k < 32; k++)
        binaryProduct[k] = 0;
    convertFromDecimalToBinary(binaryA, a);
    convertFromDecimalToBinary(binaryB, b);
    printBinaryNumber(binaryA);
    printf("\n*\n");
    printBinaryNumber(binaryB);
    printf("\n=\n");
    productTwoNumbers(binaryA, binaryB, binaryProduct);

    printBinaryNumber(binaryProduct);

    return 0;
}