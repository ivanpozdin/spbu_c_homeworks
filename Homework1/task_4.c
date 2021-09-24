#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void fillArrayOfPrimes(bool* isPrime, int N)
{
    for (int i = 2; i * i < N; i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                isPrime[j] = false;
            }
        }
    }
}
void printPrimeNumsUptoN(int N)
{
    bool* isPrime = malloc(N * sizeof(bool));
    for (int i = 2; i < N; i++)
        isPrime[i] = true;
    fillArrayOfPrimes(isPrime, N);
    printf("Простые числа до %i:\n", N);
    for (int i = 2; i < N; i++) {
        if (isPrime[i])
            printf("%i\n", i);
    }
    free(isPrime);
}

int main()
{
    int N = 0;
    printf("Введите число, до которого будут выводиться простые числа: ");
    scanf("%i", &N);
    printPrimeNumsUptoN(N);
    return 0;
}
