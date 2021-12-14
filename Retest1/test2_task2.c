#include <stdio.h>
#include <stdlib.h>

void evenInsertSort(int* array, int amountOfElements){
    for (int i = 2; i < amountOfElements; i += 2) {
        int curElement = i;
        while (curElement > 0 && array[curElement] < array[curElement - 1]) {
            int tmp = array[curElement];
            array[curElement] = array[curElement - 2];
            curElement -= 2;
            array[curElement] = tmp;
        }
    }
}

int main()
{
    int amountOfElements = 0;
    printf("Enter the amount of elements you want to be in array: ");
    scanf("%i", &amountOfElements);
    int* array = calloc(amountOfElements, sizeof(int));
    printf("If you want to enter elements, enter 0, and if you want to randomly generate them, enter 1: ");
    int variant = -1;
    scanf("%i", &variant);
    if (variant == 0) {
        printf("Enter your elements: ");
        for (int i = 0; i < amountOfElements; i++)
            scanf("%i", &array[i]);
    } else {
        for (int i = 0; i < amountOfElements; i++)
            array[i] = rand() % 32 + 11;
        printf("Your array: ");
        for (int i = 0; i < amountOfElements; i += 1)
            printf("%i ", array[i]);
        printf("\n");
    }

    evenInsertSort(array, amountOfElements);
    printf("Array with sorted even positions: ");
    for (int i = 0; i < amountOfElements; i += 1)
        printf("%i ", array[i]);

    free(array);
}
