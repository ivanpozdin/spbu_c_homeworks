#include "linked_map.h"

int main()
{
    LinkedMap* map = makeNewLinkedMap();
    char nameOfInputFile[150] = "";
    printf("Enter the name of the file whose contents you want to analyze:\n");
    scanf("%s", nameOfInputFile);
    FILE* inputFile = fopen(nameOfInputFile, "r");

    char nameOfOutputFile[150] = "";
    printf("Enter the name of the file in which you want to record the result of the frequency analysis:\n");
    scanf("%s", nameOfOutputFile);
    FILE* outputFile = fopen(nameOfOutputFile, "w");
    if (!(inputFile || outputFile)) {
        printf("There is something wrong with the files");
        exit(-1);
    }
    char word[128];
    while (fscanf(inputFile, "%s", word) != EOF) {
        if (hasKey(map, word))
            put(map, word, get(map, word, 0) + 1, 128);
        else
            put(map, word, 1, 128);
    }
    int variant = 0;
    printf("If you want to see the entire list of pairs of the form - word, occurrence - enter 0\n");
    printf("If you want to see the occurrence of specific words,\nthen enter 1, and then the number of different words, then enter these words\n");
    scanf("%i", &variant);
    if (variant == 0)
        printAllKeysAndValues(outputFile, map, ',');
    else if (variant == 1) {
        int amountOfWords = 0;
        scanf("%i", &amountOfWords);
        char key[128];
        for (int i = 0; i < amountOfWords; i++) {
            scanf("%s", key);
            fprintf(outputFile, "%s %i\n", key, get(map, key, 0));
        }
    } else {
        printf("You entered wrong variant");
    }
    deleteMap(map);
    fclose(inputFile);
    fclose(outputFile);
}
