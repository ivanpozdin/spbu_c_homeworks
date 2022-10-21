#include <stdio.h>
#include <stdlib.h>

void mergeArrays(int* leftPart, int sizeOfLeft, const int* rightPart, int sizeOfRight)
{
    int* tmpArray = calloc(sizeof(int), sizeOfLeft + sizeOfRight);
    int leftIdx = 0, rightIdx = 0, tmpArrayIdx = 0;

    while (leftIdx < sizeOfLeft || rightIdx < sizeOfRight) {
        if (leftIdx == sizeOfLeft || (rightIdx < sizeOfRight && leftPart[leftIdx] > rightPart[rightIdx]))
            tmpArray[tmpArrayIdx++] = rightPart[rightIdx++];
        else
            tmpArray[tmpArrayIdx++] = leftPart[leftIdx++];
    }
    int* wholeArray = leftPart;
    for (int i = 0; i < sizeOfLeft + sizeOfRight; i++)
        wholeArray[i] = tmpArray[i];
    free(tmpArray);
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
    free(array);
    return 0;
}