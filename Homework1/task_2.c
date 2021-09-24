#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
bool getMaximumElementOfArrayThatOccursMoreThanOnce(int* array, int arraySize, int* item)
{
    qsort(array, arraySize, sizeof(int), compare);
    bool itemIsFound = false;
    for (int i = arraySize - 2; i >= 0; i--) {
        if (array[i] == array[i + 1]) {
            itemIsFound = true;
            *item = array[i];
            break;
        }
    }
    return itemIsFound;
}
int main()
{
    int arraySize = 0, item = 0;
    printf("Введите кол-во чисел: ");
    scanf("%i", &arraySize);
    int* array = calloc(arraySize, sizeof(int));
    printf("Введите числа через пробел: ");
    for (int i = 0; i < arraySize; i++)
        scanf("%i", &array[i]);
    
    if (getMaximumElementOfArrayThatOccursMoreThanOnce(array, arraySize, &item)) {
        printf("Максимальный элемент массива, встречающийся более одного раза: %i", item);
    } else {
        printf("Максимального элемента массива, встречающегося более одного раза в массиве нет");
    }

    free(array);
    return 0;
}
