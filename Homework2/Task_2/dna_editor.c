#include "dna_editor.h"

void freePartOfList(LinkedListElement* start, LinkedListElement* end);

struct LinkedList {
    LinkedListElement* head;
};

struct LinkedListElement {
    char letter;
    LinkedListElement* nextElement;
};

typedef struct ListRange {
    LinkedListElement* start;
    LinkedListElement* end;
} ListRange;

LinkedList* createLinkedList(const char* sequence)
{
    LinkedList* list = malloc(sizeof(LinkedList));
    LinkedListElement* previousElement = malloc(sizeof(LinkedListElement));
    previousElement->letter = sequence[0];
    previousElement->nextElement = NULL;
    list->head = previousElement;
    int sequenceLength = strlen(sequence);
    for (int i = 1; i < sequenceLength; i++) {
        LinkedListElement* newElement = malloc(sizeof(LinkedListElement));
        newElement->nextElement = NULL;
        newElement->letter = sequence[i];
        previousElement->nextElement = newElement;
        previousElement = newElement;
    }
    return list;
}

ListRange* findBordersOfSequence(LinkedListElement* startOfSearch, const char* sequence)
{
    ListRange* range = malloc(sizeof(ListRange));
    range->start = NULL;
    range->end = NULL;
    for (LinkedListElement* start = startOfSearch; start; start = start->nextElement) {
        int i = 0;
        bool isSequence = true;
        LinkedListElement* end = start;
        int sequenceLength = strlen(sequence);
        while (end && i < sequenceLength) {
            if (end->letter != sequence[i])
                isSequence = false;

            if (i + 1 < strlen(sequence))
                end = end->nextElement;
            i++;
        }
        if (isSequence) {
            range->start = start;
            range->end = end;
            break;
        }
    }
    return range;
}

void delete(LinkedList* list, const char* start, const char* end)
{
    ListRange* rangeOfStart = findBordersOfSequence(list->head, start);

    LinkedListElement* lastElementBeforeStart = list->head;
    while (lastElementBeforeStart->nextElement != rangeOfStart->start) {
        lastElementBeforeStart = lastElementBeforeStart->nextElement;
    }
    ListRange* rangeOfEnd = findBordersOfSequence(rangeOfStart->start, end);

    LinkedListElement* firstElementAfterEnd = rangeOfEnd->end->nextElement;
    lastElementBeforeStart->nextElement = firstElementAfterEnd;

    freePartOfList(rangeOfStart->start, rangeOfEnd->end);
    free(rangeOfStart);
    free(rangeOfEnd);
}

void insert(LinkedList* list, const char* start, const char* fragment)
{
    ListRange* rangeStart = findBordersOfSequence(list->head, start);
    LinkedListElement* elementAfterFragment = rangeStart->end->nextElement;
    LinkedList* fragmentList = createLinkedList(fragment);

    LinkedListElement* lastElementOfFragment = fragmentList->head;
    while (lastElementOfFragment->nextElement) {
        lastElementOfFragment = lastElementOfFragment->nextElement;
    }
    rangeStart->end->nextElement = fragmentList->head;
    lastElementOfFragment->nextElement = elementAfterFragment;

    free(rangeStart);
}

void replace(LinkedList* list, const char* template, const char* fragment)
{
    LinkedList* fragmentList = createLinkedList(fragment);
    ListRange* rangeOfTemplate = findBordersOfSequence(list->head, template);

    LinkedListElement* lastElementBeforeTemplate = list->head;
    while (lastElementBeforeTemplate->nextElement != rangeOfTemplate->start) {
        lastElementBeforeTemplate = lastElementBeforeTemplate->nextElement;
    }
    LinkedListElement* firstElementAfterTemplate = rangeOfTemplate->end->nextElement;

    LinkedListElement* lastElementOfFragment = fragmentList->head;
    while (lastElementOfFragment->nextElement) {
        lastElementOfFragment = lastElementOfFragment->nextElement;
    }
    lastElementBeforeTemplate->nextElement = fragmentList->head;
    lastElementOfFragment->nextElement = firstElementAfterTemplate;

    freePartOfList(rangeOfTemplate->start, rangeOfTemplate->end);
    free(rangeOfTemplate);
}

void freePartOfList(LinkedListElement* start, LinkedListElement* end)
{
    for (LinkedListElement *current = start, *next = NULL; current != end; current = next) {
        next = current->nextElement;
        free(current);
    }
}

void freeList(LinkedList* list)
{
    freePartOfList(list->head, NULL);
    free(list);
}

void printList(FILE* outputFile, LinkedList* list)
{
    for (LinkedListElement* current = list->head; current; current = current->nextElement)
        fprintf(outputFile, "%c", current->letter);
}