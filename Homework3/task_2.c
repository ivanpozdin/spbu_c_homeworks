#include <stdbool.h>
#include <stdio.h>

typedef unsigned long long int uint64_t;
typedef union Number {
    double realNumber;
    uint64_t unsignedIntegerFormOfDouble;
} Number;

int main()
{
    Number number;
    printf("Enter a number: ");
    scanf("%lf", &number.realNumber);
    uint64_t unsignedIntegerFormOfDouble = number.unsignedIntegerFormOfDouble;
    bool binaryFormOfRealNumber[64];

    for (int i = 0; i <= 63; i++) {
        binaryFormOfRealNumber[i] = unsignedIntegerFormOfDouble & 1;
        unsignedIntegerFormOfDouble >>= 1;
    }

    double mantissa = 1, degree = 1;
    for (int i = 51; i >= 0; i--) {
        degree /= 2.0;
        mantissa += binaryFormOfRealNumber[i] * degree;
    }
    int exponent = -1023;
    for (int i = 62; i >= 52; i--)
        exponent += binaryFormOfRealNumber[i] * (1 << (i - 52));

    printf("Result: ");
    binaryFormOfRealNumber[63] == 0 ? printf("+") : printf("-");
    printf("%*.*lf*2^%i", 20, 19, mantissa, exponent);

    return 0;
}
