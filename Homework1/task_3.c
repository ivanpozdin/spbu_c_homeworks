#include <stdio.h>
#include <stdlib.h>
void swapPartsOfArray(int* array, int arraySize, int sizeOfLeftPartOfArray)
{
    for (int i = sizeOfLeftPartOfArray - 1; i >= 0; i--) {
        for (int j = i; j < arraySize - sizeOfLeftPartOfArray + i; j++) {
            int tmp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = tmp;
        }
    }
}
int main()
{
    int arraySize = 0, m = 0, n = 0;
    printf("Введите числа m и n: ");
    scanf("%i %i", &m, &n);
    arraySize = m + n;
    int* x = calloc(arraySize, sizeof(int));
    printf("Введите %i элемента(ов) массива x через пробел: ", m + n);
    for (int i = 0; i < arraySize; i++) {
        scanf("%i", &x[i]);
    }
    swapPartsOfArray(x, arraySize, m);
    printf("Массив х с переставленным началом и концом:\t");
    for (int i = 0; i < arraySize; i++) {
        printf("%i\t", x[i]);
    }
    free(x);

    return 0;
}