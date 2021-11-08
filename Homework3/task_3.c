#include <stdbool.h>
#include <stdio.h>

void fillArrayWithZeroes(bool* array, int amountOfElements)
{
    for (int i = 0; i < amountOfElements; i++)
        array[i] = 0;
}

void printBinaryNumber(bool* binaryNumber)
{
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
        printf("%d", binaryNumber[i]);
}
void convertFromDecimalToBinary(bool* binaryNumber, int decimalNumber)
{
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
        binaryNumber[i] = (bool)(1 << i & decimalNumber);
}

void addTwoBinaryNumbers(const bool* number1, const bool* number2, bool* result)
{
    bool inMind = 0;
    for (int i = 0; i < sizeof(int) * 8; i++) {
        int sum = number1[i] + number2[i] + inMind;
        result[i] = sum % 2;
        inMind = sum / 2;
    }
}

void productTwoNumbers(const bool* number1, const bool* number2, bool* result)
{
    for (int i = 0; i < sizeof(int) * 8; i++) {
        bool resultOfPrimaryProduct[32];
        fillArrayWithZeroes(resultOfPrimaryProduct, sizeof(int) * 8);

        for (int j = 0; j + i < sizeof(int) * 8; j++)
            resultOfPrimaryProduct[j + i] = number1[j] && number2[i];

        addTwoBinaryNumbers(resultOfPrimaryProduct, result, result);
    }
}

int main()
{
    int a = 0, b = 0;
    printf("Enter two integer numbers:");
    scanf("%i %i", &a, &b);

    bool binaryA[sizeof(int) * 8], binaryB[sizeof(int) * 8], binaryProduct[sizeof(int) * 8];
    fillArrayWithZeroes(binaryA, sizeof(int) * 8);
    fillArrayWithZeroes(binaryB, sizeof(int) * 8);
    fillArrayWithZeroes(binaryProduct, sizeof(int) * 8);

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