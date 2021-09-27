#include "linked_map.h"

int main()
{
    LinkedMap* map = makeNewLinkedMap();
    char* nameOfInputFile = (char*)malloc(150 * sizeof(char));
    printf("Введите название файла, содержимое которого нужно проанализоровать:\n");
    scanf("%s", nameOfInputFile);
    FILE* inputFile = fopen(nameOfInputFile, "r");

    char* nameOfOutputFile = (char*)malloc(150 * sizeof(char));
    printf("Введите название файла, в который нужно записать результат частотного анализа:\n");
    scanf("%s", nameOfOutputFile);
    FILE* outputFile = fopen(nameOfOutputFile, "w");

    char word[127];
    while (fscanf(inputFile, "%s", word) != EOF) {
        put(map, word);
    }
    int variant = 0;
    printf("Если хотите увидеть весь список пар вида - слово встречаемость - введите 0\n");
    printf("Если хотите увидеть встречаемость конкретных слов, то введите 1, а затем кол-во разных слов, после этого вводите эти слова\n");
    scanf("%i", &variant);
    if (variant == 0) {
        printResultInFile(outputFile, map);
    } else {
        int amountOfWords = 0;
        scanf("%i", &amountOfWords);
        char key[127];
        for (int i = 0; i < amountOfWords; i++) {
            scanf("%s", key);
            fprintf(outputFile, "%s %i\n", key, get(map, key));
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}
