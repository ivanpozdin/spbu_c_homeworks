#include <stdio.h>
#include <stdlib.h>

void mergeArrays(int* left, int sizeOfLeft, int* right, int sizeOfRight)
{
    int* arrayToReturn = calloc(sizeof(int), sizeOfLeft + sizeOfRight);
    int leftIdx = 0, rightIdx = 0, arrayToReturnIdx = 0;

    while (leftIdx < sizeOfLeft || rightIdx < sizeOfRight) {
        if (leftIdx == sizeOfLeft || (rightIdx < sizeOfRight && left[leftIdx] > right[rightIdx]))
            arrayToReturn[arrayToReturnIdx++] = right[rightIdx++];
        else
            arrayToReturn[arrayToReturnIdx++] = left[leftIdx++];
    }
    for (int i = 0; i < sizeOfLeft + sizeOfRight; i++)
        left[i] = arrayToReturn[i];
    free(arrayToReturn);
}

void mergeSort(int* array, int sizeOfArray)
{
    if (sizeOfArray <= 1)
        return;

    int* left = array;
    int leftSize = sizeOfArray / 2;
    mergeSort(left, leftSize);

    int* right = array + leftSize;
    int rightSize = sizeOfArray - leftSize;
    mergeSort(array + leftSize, rightSize);

    mergeArrays(left, leftSize, right, rightSize);
}

int main()
{
    int amountOfElements = 0;
    printf("Enter amount of elements: ");
    scanf("%i", &amountOfElements);

    printf("Enter elements of array: ");
    int* array = calloc(sizeof(int), amountOfElements);
    for (int i = 0; i < amountOfElements; i++)
        scanf("%i", &array[i]);

    mergeSort(array, amountOfElements);
    printf("Sorted array: ");
    for (int i = 0; i < amountOfElements; i++)
        printf("%i ", array[i]);

    return 0;
}