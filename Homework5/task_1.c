#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char nameOfInputFile[150] = "/Users/ivanpozdin/CLionProjects/spbu_c_homeworks/Homework5/shop_logs.txt";

    FILE* inputFile = fopen(nameOfInputFile, "r");

    int amountOfCommands = 0;
    fscanf(inputFile, "%i", &amountOfCommands);
    char command[128];
    TreeMap* map = createTreeMap();

    for (int i = 0; i < amountOfCommands; i++){
        fscanf(inputFile, "%s", command);
        if (strcmp(command, "ADD") == 0){
            int size = 0, count = 0;
            fscanf(inputFile, "%i", &size);
            fscanf(inputFile, "%i", &count);
            int countWas = 0;
            if (hasKey(map, wrapInt(size)))
                countWas = getInt(get(map, wrapInt(size)));
            put(map, wrapInt(size), wrapInt(count + countWas));

        } else if (strcmp(command, "GET") == 0){
            int size = 0;
            fscanf(inputFile, "%i", &size);
            printf("%i\n", getInt(get(map, wrapInt(size))));
        } else if(strcmp(command, "SELECT") == 0){
            int size = 0;
            fscanf(inputFile, "%i", &size);

            Value suitableSize = getLowerBound(map, wrapInt(size));
            if (isNone(suitableSize))
                printf("SORRY\n");
            else{
                int rightSize = getInt(suitableSize);
                printf("%i\n", getInt(suitableSize));
                int newCount = getInt(get(map, wrapInt(rightSize))) - 1;
                if (newCount == 0)
                    removeKey(map, wrapInt(rightSize));
                else
                    put(map, wrapInt(rightSize), wrapInt(newCount));
            }
        } else{
            deleteTreeMap(map);
            printf("Something went wrong :(");
            return -1;
        }
    }
    deleteTreeMap(map);

    fclose(inputFile);

    return 0;
}

#pragma clang diagnostic pop