#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char nameOfInputFile[150];
    char nameOfOutputResultsFile[150];
    char nameOfOutputBalanceFile[150];
    if (argc == 1) {
        printf("Enter the name of the file whose contents you want to analyze:\n");
        scanf("%s", nameOfInputFile);
        printf("Enter the name of the file in which you want to record the results:\n");
        scanf("%s", nameOfOutputResultsFile);
        printf("Enter the name of the file in which you want to record the balance:\n");
        scanf("%s", nameOfOutputBalanceFile);
    } else {
        strcpy(nameOfInputFile, argv[1]);
        strcpy(nameOfOutputResultsFile, argv[2]);
        strcpy(nameOfOutputBalanceFile, argv[3]);
    }
    FILE* inputFile = fopen(nameOfInputFile, "r");
    FILE* outputResultsFile = fopen(nameOfOutputResultsFile, "w");
    FILE* outputBalanceFile = fopen(nameOfOutputBalanceFile, "w");

    if (!inputFile || !outputResultsFile || !outputBalanceFile) {
        if (inputFile)
            fclose(inputFile);
        if (outputResultsFile)
            fclose(outputResultsFile);
        if (outputBalanceFile)
            fclose(outputBalanceFile);

        printf("There is something wrong with the files");
        return -1;
    }
    int amountOfCommands = 0;
    fscanf(inputFile, "%i", &amountOfCommands);
    char command[128];
    TreeMap* map = createTreeMap();

    for (int i = 0; i < amountOfCommands; i++) {
        fscanf(inputFile, "%s", command);
        if (strcmp(command, "ADD") == 0) {
            int size = 0, count = 0;
            fscanf(inputFile, "%i", &size);
            fscanf(inputFile, "%i", &count);
            int countWas = 0;
            if (hasKey(map, wrapInt(size)))
                countWas = getInt(getValueFromKey(map, wrapInt(size)));
            put(map, wrapInt(size), wrapInt(count + countWas));

        } else if (strcmp(command, "GET") == 0) {
            int size = 0;
            fscanf(inputFile, "%i", &size);
            Value resultOfGet = getValueFromKey(map, wrapInt(size));
            if (isNone(resultOfGet))
                fprintf(outputResultsFile, "0\n");
            else
                fprintf(outputResultsFile, "%i\n", getInt(resultOfGet));

        } else if (strcmp(command, "SELECT") == 0) {
            int size = 0;
            fscanf(inputFile, "%i", &size);
            Value suitableSizeValue = getLowerBound(map, wrapInt(size));
            if (isNone(suitableSizeValue))
                fprintf(outputResultsFile, "SORRY\n");
            else {
                fprintf(outputResultsFile, "%i\n", getInt(suitableSizeValue));
                int newCount = getInt(getValueFromKey(map, suitableSizeValue)) - 1;
                if (newCount == 0)
                    removeKey(map, suitableSizeValue);
                else
                    put(map, suitableSizeValue, wrapInt(newCount));
            }
        } else {
            deleteTreeMap(map);
            printf("Something went wrong :(");
            return -1;
        }
    }
    int sizeOfArray = 0;
    keyValuePair* array = getKeysValuesArray(map, &sizeOfArray);
    for (int i = 0; i < sizeOfArray; i++)
        fprintf(outputBalanceFile, "%i %i\n", getInt(array[i].key), getInt(array[i].value));

    free(array);
    deleteTreeMap(map);

    fclose(inputFile);
    fclose(outputResultsFile);
    fclose(outputBalanceFile);
}
