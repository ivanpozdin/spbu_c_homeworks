
#ifndef SPBU_C_HOMEWORKS_TEST1_VECTOR_H_
#define SPBU_C_HOMEWORKS_TEST1_VECTOR_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector Vector;

Vector* makeNewVector(int* array, int sizeOfArray);
int* getCoordinates(Vector* vec);
Vector* calculateSumOfTwoVectors(Vector* vector1, Vector* vector2);
Vector* calculateDifferenceOfTwoVectors(Vector* vector1, Vector* vector2);
double calculateScalarProduct(Vector* vector1, Vector* vector2);
double findLengthOfVector(Vector* vec);
void freeVector(Vector* vec);

#endif // SPBU_C_HOMEWORKS_TEST1_VECTOR_H_
