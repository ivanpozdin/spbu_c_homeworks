#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void print2DArray(int n, int** array)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%i\t", array[i][j]);
        printf("\n");
    }
}

void fillSpiralArray(int n, int** spiralArray)
{
    int startPos = n / 2, i = startPos, j = startPos, currentNumber = 1, curLen = 0;
    spiralArray[i][j] = currentNumber;
    while (currentNumber < n * n) {
        curLen += 1;
        while ((currentNumber != n * n) && (abs(j - startPos) < curLen)) {
            j += 1;
            currentNumber += 1;
            spiralArray[i][j] = currentNumber;
        }

        while ((currentNumber != n * n) && (abs(i - startPos) < curLen)) {
            i += 1;
            currentNumber += 1;
            spiralArray[i][j] = currentNumber;
        }
        bool flag = true;
        while ((currentNumber != n * n) && (flag || abs(j - startPos) < curLen)) {
            flag = false;
            j -= 1;
            currentNumber += 1;
            spiralArray[i][j] = currentNumber;
        }
        flag = true;
        while ((currentNumber != n * n) && (flag || abs(i - startPos) < curLen)) {
            flag = false;
            i -= 1;
            currentNumber += 1;
            spiralArray[i][j] = currentNumber;
        }
    }
}

int main()
{
    int n = 0;
    printf("Введите нечётное число n: ");
    scanf("%i", &n);

    int** spiralArray = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        spiralArray[i] = (int*)calloc(n, sizeof(int));

    fillSpiralArray(n, spiralArray);
    printf("Спираль с числами от 1 до %i\n", n * n);
    print2DArray(n, spiralArray);

    for (int i = 0; i < n; i++)
        free(spiralArray[i]);
    free(spiralArray);
    return 0;
}
