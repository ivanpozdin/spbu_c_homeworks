#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b)
{
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}
void printMaximumElementOfArrayThatOccursMoreThanOnce(int* array, int arraySize)
{
    qsort(array, arraySize, sizeof(int), compare);
    int cnt = 0;
    int itemIsFound = 0;
    int item = 0;
    for (int i = arraySize - 1; i >= 0; i--) {
        if (cnt == 0) {
            cnt = 1;
        } else {
            if (array[i] == array[i + 1]) {
                itemIsFound = 1;
                item = array[i];
                break;
            } else {
                cnt = 1;
            }
        }
    }
    if (itemIsFound) {
        printf("Максимальный элемент массива, встречающийся более одного раза: %i", item);
    } else {
        printf("Максимального элемента массива, встречающегося более одного раза в массиве нет");
    }
}
int main()
{
    int arraySize = 0;
    printf("Введите кол-во чисел: ");
    scanf("%i", &arraySize);
    int* array = calloc(arraySize, sizeof(int));
    printf("Введите числа через пробел: ");
    for (int i = 0; i < arraySize; i++) {
        scanf("%i", &array[i]);
    }
    printMaximumElementOfArrayThatOccursMoreThanOnce(array, arraySize);

    free(array);
    return 0;
}
