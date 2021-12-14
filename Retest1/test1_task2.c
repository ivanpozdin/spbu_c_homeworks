#include <stdio.h>

int main()
{
    char nameOfInputFile[150] = "";
    char nameOfOutputFile[150] = "";
    printf("Enter the name of the file whose contents you want to analyze:\n");
    scanf("%s", nameOfInputFile);
    printf("Enter the name of the file in which you want to record the result of the frequency analysis:\n");
    scanf("%s", nameOfOutputFile);
    FILE* inputFile = fopen(nameOfInputFile, "r");
    FILE* outputFile = fopen(nameOfOutputFile, "w");
    char c = '0';
    long long statistic[26];
    for (int i = 0; i < 26; i++)
        statistic[i] = 0;

    while ((c = getc(inputFile)) != EOF)
        if ((int)c > 96 && (int)c < 123)
            statistic[(int)c - 97]++;

    for (int i = 0; i < 26; i++)
        if (statistic[i] > 0)
            fprintf(outputFile, "%c: %lli\n", (char)(97 + i), statistic[i]);

    fclose(inputFile);
    fclose(outputFile);
}
