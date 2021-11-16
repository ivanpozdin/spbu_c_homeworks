#include <stdio.h>
#include <stdlib.h>

int* mergeArrays(const int* array1, const int* array2, int size1, int size2)
{

    int* resultArray = calloc(size1 + size2, sizeof(int));
    int idx1 = 0, idx2 = 0;
    for (int idxOfResult = 0; idxOfResult < size1 + size2; idxOfResult++) {
        if (idx1 == size1)
            resultArray[idxOfResult] = array2[idx2++];

        else if (idx2 == size2)
            resultArray[idxOfResult] = array1[idx1++];

        else {
            if (array1[idx1] > array2[idx2])
                resultArray[idxOfResult] = array1[idx1++];
            else
                resultArray[idxOfResult] = array2[idx2++];
        }
    }
    return resultArray;
}

int main()
{
    int size1, size2;
    printf("Enter size of first array: ");
    scanf("%i", &size1);
    printf("Enter elements of first array: ");
    int* array1 = calloc(size1, sizeof(int));
    for (int i = 0; i < size1; i++)
        scanf("%i", &array1[i]);

    printf("Enter size of second array: ");
    scanf("%i", &size2);
    printf("Enter elements of second array: ");
    int* array2 = calloc(size2, sizeof(int));
    for (int i = 0; i < size2; i++)
        scanf("%i", &array2[i]);

    printf("Merged arrays:\n");
    int* resultArray = mergeArrays(array1, array2, size1, size2);
    for (int i = 0; i < size1 + size2; i++)
        printf("%i ", resultArray[i]);

    /* Алгоритм работает за О(max(n, m)) где m и n -- размеры массивов.*/
}
