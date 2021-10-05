#include "Vector.h"

int main()
{
    int sizeOfVectors = 0;
    printf("Enter size of vectors:");
    scanf("%i", &sizeOfVectors);
    int* array1 = calloc(sizeof(int), sizeOfVectors);
    int* array2 = calloc(sizeof(int), sizeOfVectors);
    printf("enter first Vector:\n");
    for (int j = 0; j < sizeOfVectors; j++) {
        scanf("%i", &array1[j]);
    }
    printf("enter second Vector\n");
    for (int j = 0; j < sizeOfVectors; j++) {
        scanf("%i", &array2[j]);
    }
    Vector* vector1 = makeNewVector(array1, sizeOfVectors);
    Vector* vector2 = makeNewVector(array2, sizeOfVectors);

    printf("length of vector2: %f\n", findLengthOfVector(vector2));
    printf("scalar product of vector1 and vector2 = %i\n", calculateScalarProduct(vector1, vector2));
    Vector* vector3 = calculateSumOfTwoVectors(vector1, vector2);
    Vector* vector4 = calculateDifferenceOfTwoVectors(vector1, vector2);
    int* vector3Coordinates = getCoordinates(vector3);
    int* vector4Coordinates = getCoordinates(vector4);
    printf("coordinates of sum of vectors:\n");
    for (int i = 0; i < sizeOfVectors; i++) {
        printf("%i ", vector3Coordinates[i]);
    }
    printf("\n");
    printf("coordinates of difference of vectors:\n");
    for (int i = 0; i < sizeOfVectors; i++) {
        printf("%i ", vector4Coordinates[i]);
    }
    printf("\n");
    return 0;
}
