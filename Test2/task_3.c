#include <stdio.h>
#include <stdlib.h>
typedef struct Date {
    int day;
    int month;
    int year;
} Date;

Date* isStringADate(char* dateProbably)
{
    if (dateProbably[2] != '.' || dateProbably[3] != '.')
        return NULL;

    int d1 = dateProbably[0] - '0';
    int d2 = dateProbably[1] - '0';
    int m1 = dateProbably[3] - '0';
    int m2 = dateProbably[4] - '0';
    int y1 = dateProbably[6] - '0';
    int y2 = dateProbably[7] - '0';
    int y3 = dateProbably[8] - '0';
    int y4 = dateProbably[9] - '0';
    if (d1 < 0 || d1 > 9 || d2 < 0 || d2 > 9 || m1 < 0 || m1 > 9 || m2 < 0 || m2 > 9 || y1 < 0 || y1 > 9 || y2 < 0 || y2 > 9 || y3 < 0 || y3 > 9 || y4 < 0 || y4 > 9)
        return NULL;
    int day = d1 * 10 + d2;
    int month = m1 * 10 + m2;
    int year = y1 * 1000 + y2 * 100 + y3 * 10 + y4;

    if (day <= 31 && month <= 12) {
        Date* date = malloc(sizeof(Date));
        date->day = day;
        date->month = month;
        date->year = year;
        return date;
    }
    return NULL;
}

void printDate(Date* date)
{
    if (!date) {
        if (date->day <= 9)
            printf("0%i.", date->day);
        else
            printf("%i.", date->day);
        if (date->month <= 9)
            printf("0%i.", date->month);
        else
            printf("%i.", date->month);
        if (date->year <= 9)
            printf("000%i", date->year);
        else if (date->year <= 99)
            printf("00%i", date->year);
        else if (date->year <= 999)
            printf("0%i", date->year);
        else
            printf("%i", date->year);
    }
}

int main()
{

    char nameOfInputFile[150] = "";
    printf("Enter the name of the file whose contents you want to analyze:\n");
    scanf("%s", nameOfInputFile);
    FILE* inputFile = fopen(nameOfInputFile, "r");

    char word[128];
    Date* minDate = malloc(sizeof(Date));
    minDate->day = 31;
    minDate->month = 12;
    minDate->year = 9999;
    while (fscanf(inputFile, "%s", word) != EOF) {
        Date* dateProbably = isStringADate(word);
        if (!dateProbably)
            continue;
        else {
            if ((minDate->year > dateProbably->year)
                || (minDate->year >= dateProbably->year && minDate->month > dateProbably->month)
                || (minDate->year >= dateProbably->year && minDate->month >= dateProbably->month && minDate->day <= dateProbably->day)) {
                minDate->year = dateProbably->year;
                minDate->month = dateProbably->month;
                minDate->day = dateProbably->day;
            }
        }
        if (dateProbably)
            free(dateProbably);
    }
    printDate(minDate);
    free(minDate);
}
