#include <stdio.h>
#include <stdlib.h>

typedef struct Position {
    int value;
    int i;
    int j;
} Position;

Position* findSaddlePoints(int** array, int nColumns, int nRaws, int* saddlePointsArraySize)
{
    *saddlePointsArraySize = 1000;
    Position* saddlePoints = malloc(sizeof(Position) * *saddlePointsArraySize);
    int idx = 0;
    for (int i = 0; i < nRaws; i++) {
        Position minElementInRaw = (Position) { array[i][0], i, 0 };
        for (int j = 0; j < nColumns; j++)
            if (array[i][j] < minElementInRaw.value)
                minElementInRaw = (Position) { array[i][j], i, j };

        Position minElementInColumn = (Position) { array[i][minElementInRaw.j] };
        for (int x = 0; x < nRaws; x++)
            if (array[x][minElementInRaw.j] < minElementInRaw.value)
                minElementInColumn = (Position) { array[x][minElementInRaw.j], x, minElementInRaw.j };
        if (minElementInRaw.i == minElementInColumn.i && minElementInRaw.j == minElementInColumn.j) {
            saddlePoints[idx] = minElementInRaw;
            idx += 1;
            if (idx == *saddlePointsArraySize) {
                (*saddlePointsArraySize) *= 2;
                saddlePoints = realloc(saddlePoints, *saddlePointsArraySize);
                if (!saddlePoints) {
                    printf("Memory was not allocated");
                    exit(-1);
                }
            }
        }
    }
    *saddlePointsArraySize = idx;
    saddlePoints = realloc(saddlePoints, *saddlePointsArraySize);
    if (!saddlePoints) {
        printf("Memory was not allocated");
        exit(-1);
    }
    return saddlePoints;
}

int main()
{
    int nColumns = 0;
    int nRaws = 0;
    printf("Enter amount of columns: ");
    scanf("%i", &nColumns);
    printf("Enter amount of raws: ");
    scanf("%i", &nRaws);
    int** array = malloc(sizeof(int*) * nRaws);
    for (int i = 0; i < nRaws; i++)
        array[i] = malloc(sizeof(int) * nColumns);

    printf("Enter elements of array:\n");
    for (int i = 0; i < nRaws; i++)
        for (int j = 0; j < nColumns; j++)
            scanf("%i", &array[i][j]);

    int saddlePointsArraySize = 0;
    Position* saddlePoints = findSaddlePoints(array, nColumns, nRaws, &saddlePointsArraySize);
    printf("Saddle points of array: \n");
    for (int i = 0; i < saddlePointsArraySize; i++)
        printf("value: %i, raw: %i, column: %i\n", saddlePoints[i].value, saddlePoints[i].i, saddlePoints[i].j);

    for (int i = 0; i < nRaws; i++)
        free(array[i]);
    free(array);
    free(saddlePoints);
}