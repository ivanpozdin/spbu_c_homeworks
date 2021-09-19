#include <stdio.h>
#include <stdlib.h>

void printPrimeNumsUptoN(int N)
{
    char* isNotPrime = calloc(N, sizeof(char));
    for (int i = 2; i * i < N; i++) {
        if (!isNotPrime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                isNotPrime[j] = 1;
            }
        }
    }
    printf("Простые числа до %i:\n", N);
    for (int i = 2; i < N; i++) {
        if (!isNotPrime[i]) {
            printf("%i\n", i);
        }
    }
    free(isNotPrime);
}

int main()
{
    int N = 0;
    printf("Введите число, до которого будут выводиться простые числа: ");
    scanf("%i", &N);
    printPrimeNumsUptoN(N);
    return 0;
}
