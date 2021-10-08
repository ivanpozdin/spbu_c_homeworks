#include "linked_map.h"

int main(int argc, char* argv[], char* envp[])
{
    LinkedMap* map = makeNewLinkedMap();

    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");

    if ((bool)inputFile ^ (bool)outputFile) {
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
