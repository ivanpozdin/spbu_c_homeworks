#include "dna_editor.h"

int main(int argc, char* argv[], char* envp[])
{
    char nameOfInputFile[150] = "";
    scanf("%s", nameOfInputFile);
    FILE* inputFile = fopen(nameOfInputFile, "r");

    char nameOfOutputFile[150] = "";
    scanf("%s", nameOfOutputFile);
    FILE* outputFile = fopen(nameOfOutputFile, "w");
    if ((bool)inputFile ^ (bool)outputFile) {
        if (inputFile)
            fclose(inputFile);
        if (outputFile)
            fclose(outputFile);

        printf("There is something wrong with the files");
        return -1;
    }

    int sizeOfSequence;
    fscanf(inputFile, "%i", &sizeOfSequence);

    char* sequence = malloc(sizeof(char) * (sizeOfSequence + 1));
    fscanf(inputFile, "%s", sequence);

    LinkedList* list = createLinkedList(sequence);
    int amountOfCommands = 0;
    fscanf(inputFile, "%i", &amountOfCommands);

    for (int i = 0; i < amountOfCommands; i++) {
        char argument1[8], argument2[128], argument3[128];
        fscanf(inputFile, "%s %s %s", argument1, argument2, argument3);

        if (strcmp(argument1, "DELETE") == 0)
            delete (list, argument2, argument3);
        else if (strcmp(argument1, "INSERT") == 0)
            insert(list, argument2, argument3);
        else if (strcmp(argument1, "REPLACE") == 0)
            replace(list, argument2, argument3);

        printList(outputFile, list);
        fprintf(outputFile, "\n");
    }

    free(sequence);
    freeList(list);
    return 0;
}
