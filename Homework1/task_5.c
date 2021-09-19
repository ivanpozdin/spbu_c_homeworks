#include <stdio.h>
#include <stdlib.h>
void print2DArray(int n, int** array)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%i\t", *(*(array + i) + j));
        }
        printf("\n");
    }
}

void printSpiral(int n)
{
    int** spiralArray = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        spiralArray[i] = (int*)calloc(n, sizeof(int));

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
        int flag = 1;
        while ((currentNumber != n * n) && (flag || abs(j - startPos) < curLen)) {
            flag = 0;
            j -= 1;
            currentNumber += 1;
            spiralArray[i][j] = currentNumber;
        }
        flag = 1;
        while ((currentNumber != n * n) && (flag || abs(i - startPos) < curLen)) {
            flag = 0;
            i -= 1;
            currentNumber += 1;
            spiralArray[i][j] = currentNumber;
        }
    }
    print2DArray(n, spiralArray);
    for (int i = 0; i < n; i++) {
        free(spiralArray[i]);
    }
    free(spiralArray);
}

int main()
{
    int n;
    printf("Введите нечётное число n: ");
    scanf("%i", &n);
    printf("Спираль с числами от 1 до %i\n", n * n);
    printSpiral(n);
    return 0;
}
