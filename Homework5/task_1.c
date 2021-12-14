#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char nameOfInputFile[150] = "/Users/ivanpozdin/CLionProjects/spbu_c_homeworks/Homework5/shop_logs.txt";
    char nameOfOutputFile[150] = "/Users/ivanpozdin/CLionProjects/spbu_c_homeworks/Homework5/out.txt";
    //        if (argc == 1) {
    //            //printf("Enter the name of the file whose contents you want to analyze:\n");
    //            scanf("%s", nameOfInputFile);
    //            //printf("Enter the name of the file in which you want to record the result of the frequency analysis:\n");
    //            scanf("%s", nameOfOutputFile);
    //        } else {
    //            strcpy(nameOfInputFile, argv[1]);
    //            strcpy(nameOfOutputFile, argv[2]);
    //        }
    FILE* inputFile = fopen(nameOfInputFile, "r");
    FILE* outputFile = fopen(nameOfOutputFile, "w");

    if (!inputFile || !outputFile) {
        if (inputFile)
            fclose(inputFile);
        if (outputFile)
            fclose(outputFile);

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
                countWas = getInt(get(map, wrapInt(size)));
            put(map, wrapInt(size), wrapInt(count + countWas));

        } else if (strcmp(command, "GET") == 0) {
            int size = 0;
            fscanf(inputFile, "%i", &size);
            Value resultOfGet = get(map, wrapInt(size));
            if (isNone(resultOfGet))
                fprintf(outputFile, "0\n");
            else
                fprintf(outputFile, "%i\n", getInt(resultOfGet));

        } else if (strcmp(command, "SELECT") == 0) {
            int size = 0;
            fscanf(inputFile, "%i", &size);
            Value suitableSizeValue = getLowerBound(map, wrapInt(size));
            if (isNone(suitableSizeValue))
                fprintf(outputFile, "SORRY\n");
            else {
                fprintf(outputFile, "%i\n", getInt(suitableSizeValue));
                int newCount = getInt(get(map, suitableSizeValue)) - 1;
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
    deleteTreeMap(map);

    fclose(inputFile);
    fclose(outputFile);
}
