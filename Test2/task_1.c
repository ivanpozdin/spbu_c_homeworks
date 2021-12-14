#include <stdio.h>

long long getFibonacciNumber(long long number)
{
    if (number > 90 || number < 0)
        return -1;
    if (number == 0)
        return 0;
    if (number == 1 || number == 2)
        return 1;
    long long first = 1, second = 1, tmp = 0;
    for (long long i = 3; i < number; i++) {
        tmp = second;
        second = first + second;
        first = tmp;
    }
    return second;
}

int main()
{
    long long number = 0;
    printf("Please, enter number of fibonacci number less than 91: ");
    scanf("%lli", &number);
    if (number > 90 || number < 0)
        printf("Wrong number");
    else
        printf("%lli", getFibonacciNumber(number));
}