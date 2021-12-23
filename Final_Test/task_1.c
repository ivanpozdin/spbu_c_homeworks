#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NumberAndOccurrence {
    int number;
    int occurrence;
} NumberAndOccurrence;

void addElementToArray(int element, NumberAndOccurrence* array, int* amountOfElements)
{
    bool didAmountChanged = true;
    array[*amountOfElements].number = element;
    array[*amountOfElements].occurrence = 1;
    for (int i = *amountOfElements; i >= 0; i--) {
        if (array[i].number < array[i - 1].number) {
            int tmpNumber = array[i - 1].number;
            int tmpOccurrence = array[i - 1].occurrence;
            array[i - 1].number = array[i].number;
            array[i - 1].occurrence = array[i].occurrence;
            array[i].number = tmpNumber;
            array[i].occurrence = tmpOccurrence;
        }
        if (array[i].number == array[i - 1].number) {
            array[i - 1].occurrence++;

            for (int j = i; j < *amountOfElements; j++) {
                array[j].number = array[j + 1].number;
                array[j].occurrence = array[j + 1].occurrence;
            }
            didAmountChanged = false;
            break;
        }
    }
    if (didAmountChanged)
        (*amountOfElements)++;
}

int main()
{
    int arraySize = 1000;
    NumberAndOccurrence* array = malloc(sizeof(NumberAndOccurrence) * arraySize);
    int amountOfElements = 0;
    int inputNumber;
    scanf("%i", &inputNumber);
    while (inputNumber != 0) {
        if (amountOfElements == arraySize) {
            arraySize *= 2;
            array = realloc(array, arraySize);
            if (!array) {
                printf("Memory was not allocated :((");
                return -1;
            }
        }
        addElementToArray(inputNumber, array, &amountOfElements);
        scanf("%i", &inputNumber);
    }
    for (int i = 0; i < amountOfElements; i++)
        printf("Number: %i, Occurrence: %i\n", array[i].number, array[i].occurrence);

    free(array);
}
