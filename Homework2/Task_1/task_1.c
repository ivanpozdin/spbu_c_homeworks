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

    char word[128];
    while (fscanf(inputFile, "%s", word) != EOF) {
        put(map, word, 128);
    }
    int variant = 0;
    printf("If you want to see the entire list of pairs of the form - the word occurrence - enter 0\n");
    printf("If you want to see the occurrence of specific words, then enter 1, and then the number of different words, then enter these words\n");
    scanf("%i", &variant);
    if (variant == 0)
        printResultInFile(outputFile, map);
    else {
        int amountOfWords = 0;
        scanf("%i", &amountOfWords);
        char key[127];
        for (int i = 0; i < amountOfWords; i++) {
            scanf("%s", key);
            fprintf(outputFile, "%s %i\n", key, get(map, key));
        }
    }
    deleteMap(map);
    fclose(inputFile);
    fclose(outputFile);
}
