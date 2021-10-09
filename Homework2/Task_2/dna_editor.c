#include "dna_editor.h"

void freePartOfList(LinkedListElement* start, LinkedListElement* end);

struct LinkedList {
    LinkedListElement* head;
};

struct LinkedListElement {
    char letter;
    LinkedListElement* nextElement;
};

LinkedList* createLinkedList(const char* sequence)
{
    LinkedList* list = malloc(sizeof(LinkedList));
    LinkedListElement* previousElement = malloc(sizeof(LinkedListElement));
    previousElement->letter = sequence[0];
    previousElement->nextElement = NULL;
    list->head = previousElement;
    for (int i = 1; i < strlen(sequence); i++) {
        LinkedListElement* newElement = malloc(sizeof(LinkedListElement));
        previousElement->nextElement = newElement;
        newElement->nextElement = NULL;
        newElement->letter = sequence[i];
        previousElement = newElement;
    }
    return list;
}

LinkedListElement* findFirstElementOfSequence(LinkedList* list, const char* sequence)
{
    for (LinkedListElement* current1 = list->head; current1; current1 = current1->nextElement) {
        int i = 0;
        bool isSequence = true;
        LinkedListElement* current2 = current1;
        while (current2 && i < strlen(sequence) && isSequence) {
            if (current2->letter != sequence[i])
                isSequence = false;

            current2 = current2->nextElement;
            i++;
        }
        if (isSequence)
            return current1;
    }
    return NULL;
}

LinkedListElement* findLastElementOfSequence(struct LinkedListElement* start, const char* sequence)
{
    for (LinkedListElement* current1 = start; current1; current1 = current1->nextElement) {
        int i = 0;
        bool isSequence = true;
        LinkedListElement* current2 = current1;
        while (current2 && i < strlen(sequence)) {
            if (current2->letter != sequence[i])
                isSequence = false;

            if (i + 1 < strlen(sequence))
                current2 = current2->nextElement;
            i++;
        }
        if (isSequence)
            return current2;
    }
    return NULL;
}

void delete (LinkedList* list, const char* start, const char* end)
{
    LinkedListElement* firstElementOfStart = findFirstElementOfSequence(list, start);

    LinkedListElement* lastElementBeforeStart = list->head;
    while (lastElementBeforeStart->nextElement != firstElementOfStart) {
        lastElementBeforeStart = lastElementBeforeStart->nextElement;
    }
    LinkedListElement* lastElementOfEnd = findLastElementOfSequence(firstElementOfStart, end);
    LinkedListElement* firstElementAfterEnd = lastElementOfEnd->nextElement;
    lastElementBeforeStart->nextElement = firstElementAfterEnd;
    freePartOfList(firstElementOfStart, lastElementOfEnd);
}

void insert(LinkedList* list, const char* start, const char* fragment)
{
    LinkedListElement* elementBeforeFragment = findLastElementOfSequence(list->head, start);
    LinkedListElement* elementAfterFragment = elementBeforeFragment->nextElement;
    LinkedList* fragmentList = createLinkedList(fragment);

    LinkedListElement* lastElementOfFragment = fragmentList->head;
    while (lastElementOfFragment->nextElement) {
        lastElementOfFragment = lastElementOfFragment->nextElement;
    }
    elementBeforeFragment->nextElement = fragmentList->head;
    lastElementOfFragment->nextElement = elementAfterFragment;
}

void replace(LinkedList* list, const char* template, const char* fragment)
{
    LinkedList* fragmentList = createLinkedList(fragment);
    LinkedListElement* firstElementOfTemplate = findFirstElementOfSequence(list, template);
    LinkedListElement* lastElementOfTemplate = findLastElementOfSequence(list->head, template);

    LinkedListElement* lastElementBeforeTemplate = list->head;
    while (lastElementBeforeTemplate->nextElement != firstElementOfTemplate) {
        lastElementBeforeTemplate = lastElementBeforeTemplate->nextElement;
    }
    LinkedListElement* firstElementAfterTemplate = lastElementOfTemplate->nextElement;

    LinkedListElement* lastElementOfFragment = fragmentList->head;
    while (lastElementOfFragment->nextElement) {
        lastElementOfFragment = lastElementOfFragment->nextElement;
    }
    lastElementBeforeTemplate->nextElement = fragmentList->head;
    lastElementOfFragment->nextElement = firstElementAfterTemplate;

    freePartOfList(firstElementOfTemplate, lastElementOfTemplate);
}

void freePartOfList(LinkedListElement* start, LinkedListElement* end)
{
    LinkedListElement* previous = start;
    LinkedListElement* current = start->nextElement;
    while (current != end) {
        free(previous);
        previous = current;
        current = current->nextElement;
    }
    free(previous);
}

void freeList(LinkedList* list)
{
    freePartOfList(list->head, NULL);
    free(list);
}

void printList(FILE* outputFile, LinkedList* list)
{
    for (LinkedListElement* current = list->head; current; current = current->nextElement) {
        fprintf(outputFile, "%c", current->letter);
    }
}