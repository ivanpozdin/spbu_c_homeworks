#include "linked_map.h"

int main(int argc, char* argv[], char* envp[])
{
    char nameOfInputFile[150] = "";
    char nameOfOutputFile[150] = "";
    if (argc == 1) {
        printf("Enter the name of the file whose contents you want to analyze:\n");
        scanf("%s", nameOfInputFile);
        printf("Enter the name of the file in which you want to record the result of the frequency analysis:\n");
        scanf("%s", nameOfOutputFile);
    } else {
        strcpy(nameOfInputFile, argv[1]);
        strcpy(nameOfOutputFile, argv[2]);
    }
    FILE* inputFile = fopen(nameOfInputFile, "r");
    FILE* outputFile = fopen(nameOfOutputFile, "w");

    LinkedMap* map = makeNewLinkedMap();

    if (!inputFile || !outputFile) {
        if (inputFile)
            fclose(inputFile);
        if (outputFile)
            fclose(outputFile);

        printf("There is something wrong with the files");
        return -1;
    }
    char word[128];
    while (fscanf(inputFile, "%s", word) != EOF) {
        put(map, word, get(map, word, 0) + 1);
    }

    printAllKeysAndValues(outputFile, map, ',');

    deleteMap(map);
    fclose(inputFile);
    fclose(outputFile);
}
