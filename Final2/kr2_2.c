#include "DoublyLinkedList/doubly_linked_list.h"
#include <stdio.h>

bool isListSymmetric(List* list, int size)
{
    ListIterator* leftIterator = makeIteratorFromHead(list);
    ListIterator* rightIterator = makeIteratorFromTail(list);
    for (int i = 0; i < size / 2; i++) {
        if (iteratorData(leftIterator) != iteratorData(rightIterator))
            return false;
        if (!isValidIterator(leftIterator) && !isValidIterator(rightIterator)) {
            printf("Something went wrong\n");
            return false;
        }

        nextIterator(leftIterator);
        previousIterator(rightIterator);
    }
    deleteIterator(leftIterator);
    deleteIterator(rightIterator);
    return true;
}

int main()
{
    List* list = makeNewList();

    char nameOfInputFile[150] = "";

    printf("Enter the name of the file whose contents you want to analyze:\n");
    scanf("%s", nameOfInputFile);

    FILE* inputFile = fopen(nameOfInputFile, "r");

    if (!inputFile) {
        printf("There is something wrong with the files");
        return -1;
    }
    int number = 0, idx = 0;
    while (fscanf(inputFile, "%i", &number) != EOF) {
        insert(number, idx, list);
        idx++;
    }
    printList(list);
    printf("Is list symmetric? : ");
    if (isListSymmetric(list, idx))
        printf("Yes");
    else
        printf("NO");

    deleteList(list);
}
