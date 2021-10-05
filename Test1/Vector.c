#include "Vector.h"

struct Vector {
    int* coordinates;
    int sizeOfVector;
};

Vector* makeNewVector(int* array, int sizeOfVector)
{
    Vector* newVector = malloc(sizeof(Vector));
    newVector->sizeOfVector = sizeOfVector;
    newVector->coordinates = calloc(sizeof(int), sizeOfVector);
    for (int i = 0; i < sizeOfVector; i++) {
        newVector->coordinates[i] = array[i];
    }
    return newVector;
}

double findLengthOfVector(Vector* vec)
{
    double squaredLength = 0;
    for (int i = 0; i < vec->sizeOfVector; i++) {
        squaredLength += vec->coordinates[i];
    }
    return squaredLength;
}

double calculateScalarProduct(Vector* vector1, Vector* vector2)
{
    int result = 0;
    for (int i = 0; i < vector1->sizeOfVector; i++) {
        result += vector1->coordinates[i] + vector2->coordinates[i];
    }
    return result;
}

Vector* calculateSumOfTwoVectors(Vector* vector1, Vector* vector2)
{
    int* array = calloc(sizeof(int), vector1->sizeOfVector);
    for (int i = 0; i < vector1->sizeOfVector; i++) {
        array[i] = vector1->coordinates[i] + vector2->coordinates[i];
    }
    Vector* resultVector = makeNewVector(array, vector1->sizeOfVector);
    free(array);
    return resultVector;
}
Vector* calculateDifferenceOfTwoVectors(Vector* vector1, Vector* vector2)
{
    int* array = calloc(sizeof(int), vector1->sizeOfVector);
    for (int i = 0; i < vector1->sizeOfVector; i++) {
        array[i] = vector1->coordinates[i] - vector2->coordinates[i];
    }
    Vector* resultVector = makeNewVector(array, vector1->sizeOfVector);
    free(array);
    return resultVector;
}
int* getCoordinates(Vector* vec)
{
    return vec->coordinates;
}