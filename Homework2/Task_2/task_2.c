#include "dna_editor.h"

int main()
{
    int sizeOfSequence;
    scanf("%i", &sizeOfSequence);
    char* sequence = malloc(sizeof(char) * (sizeOfSequence + 1));
    scanf("%s", sequence);
    LinkedList* list = createLinkedList(sequence);
    char commands[3][8] = { "DELETE", "INSERT", "REPLACE" };
    int amountOfCommands = 0;
    scanf("%i", &amountOfCommands);
    for (int i = 0; i < amountOfCommands; i++) {
        char argument1[8];
        char argument2[128];
        char argument3[128];
        scanf("%s", argument1);
        scanf("%s", argument2);
        scanf("%s", argument3);
        if (strcmp(argument1, "DELETE") == 0) {
            delete (list, argument2, argument3);
            printList(list);
        } else if (strcmp(argument1, "INSERT") == 0) {
            insert(list, argument2, argument3);
            printList(list);
        } else if (strcmp(argument1, "REPLACE") == 0) {
            replace(list, argument2, argument3);
            printList(list);
        }
    }
    return 0;
}
