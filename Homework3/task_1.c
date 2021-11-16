#include <stdbool.h>
#include <stdio.h>

void printBinaryNumber(bool* binaryNumber)
{
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
        printf("%d", binaryNumber[i]);
}

void convertFromIntToBinary(bool* binaryNumber, int decimalNumber)
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

void fillArrayWithZeroes(bool* array, int amountOfElements)
{
    for (int i = 0; i < amountOfElements; i++)
        array[i] = 0;
}

int main()
{
    int a = 0, b = 0;
    printf("Enter two integer numbers: ");
    scanf("%i %i", &a, &b);

    bool binaryA[sizeof(int) * 8], binaryB[sizeof(int) * 8], binarySum[sizeof(int) * 8];
    fillArrayWithZeroes(binaryA, sizeof(int) * 8);
    fillArrayWithZeroes(binaryB, sizeof(int) * 8);
    fillArrayWithZeroes(binarySum, sizeof(int) * 8);

    convertFromIntToBinary(binaryA, a);
    convertFromIntToBinary(binaryB, b);
    printf("First number in binary form:\n");
    printBinaryNumber(binaryA);
    printf("\nSecond number in binary form:\n");
    printBinaryNumber(binaryB);
    addTwoBinaryNumbers(binaryA, binaryB, binarySum);
    printf("\nSum of the numbers in decimal form: %i, in binary form:\n", a + b);
    printBinaryNumber(binarySum);

    return 0;
}