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

int main()
{
    int a, b;
    printf("Enter two integer numbers: ");
    scanf("%i %i", &a, &b);
    bool binaryA[32], binaryB[32], binarySum[32];
    convertFromDecimalToBinary(binaryA, a);
    convertFromDecimalToBinary(binaryB, b);
    printf("First number in binary form:\n");
    printBinaryNumber(binaryA);
    printf("\nSecond number in binary form:\n");
    printBinaryNumber(binaryB);
    addTwoBinaryNumbers(binaryA, binaryB, binarySum);
    printf("\nSum of the numbers in decimal form: %i, in binary form:\n", a + b);
    printBinaryNumber(binarySum);

    return 0;
}