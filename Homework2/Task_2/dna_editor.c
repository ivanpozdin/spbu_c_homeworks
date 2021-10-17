#include "dna_editor.h"

void freePartOfList(LinkedListElement* start, LinkedListElement* end);

struct LinkedList {
    LinkedListElement* head;
    LinkedListElement* tail;
};

struct LinkedListElement {
    char letter;
    LinkedListElement* nextElement;
};

typedef struct ListRange {
    LinkedListElement* start;
    LinkedListElement* end;
    LinkedListElement* elementBeforeStart;
} ListRange;

LinkedList* createLinkedListFromSequence(const char* sequence)
{
    LinkedList* list = malloc(sizeof(LinkedList));
    LinkedListElement* previousElement = malloc(sizeof(LinkedListElement));
    previousElement->letter = sequence[0];
    previousElement->nextElement = NULL;
    list->head = previousElement;
    list->tail = NULL;
    int sequenceLength = strlen(sequence);
    for (int i = 1; i < sequenceLength; i++) {
        LinkedListElement* newElement = malloc(sizeof(LinkedListElement));
        newElement->nextElement = NULL;
        newElement->letter = sequence[i];
        previousElement->nextElement = newElement;
        previousElement = newElement;
        list->tail = newElement;
    }
    return list;
}

ListRange* findBordersOfSequence(LinkedListElement* startOfSearch, const char* sequence)
{
    ListRange* range = malloc(sizeof(ListRange));
    range->start = NULL;
    range->end = NULL;
    range->elementBeforeStart = NULL;
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
        range->elementBeforeStart = start;
    }
    return range;
}

bool delete (LinkedList* list, const char* start, const char* end)
{
    ListRange* rangeOfStart = findBordersOfSequence(list->head, start);
    if (!rangeOfStart->start)
        return false;

    LinkedListElement* lastElementBeforeStart = rangeOfStart->elementBeforeStart;

    ListRange* rangeOfEnd = findBordersOfSequence(rangeOfStart->end->nextElement, end);

    LinkedListElement* firstElementAfterEnd = rangeOfEnd->end->nextElement;

    if (!firstElementAfterEnd)
        list->tail = lastElementBeforeStart;

    lastElementBeforeStart->nextElement = firstElementAfterEnd;

    freePartOfList(rangeOfStart->start, rangeOfEnd->end);
    free(rangeOfStart);
    free(rangeOfEnd);
    return true;
}

bool insert(LinkedList* list, const char* start, const char* fragment)
{
    ListRange* rangeStart = findBordersOfSequence(list->head, start);
    if (!rangeStart->start)
        return false;
    LinkedListElement* elementAfterFragment = rangeStart->end->nextElement;
    LinkedList* fragmentList = createLinkedListFromSequence(fragment);

    LinkedListElement* lastElementOfFragment = fragmentList->tail;

    if (!elementAfterFragment)
        list->tail = lastElementOfFragment;

    rangeStart->end->nextElement = fragmentList->head;
    lastElementOfFragment->nextElement = elementAfterFragment;

    free(rangeStart);
    return true;
}

bool replace(LinkedList* list, const char* template, const char* fragment)
{
    LinkedList* fragmentList = createLinkedListFromSequence(fragment);
    ListRange* rangeOfTemplate = findBordersOfSequence(list->head, template);

    if (!rangeOfTemplate->start)
        return false;

    LinkedListElement* lastElementBeforeTemplate = rangeOfTemplate->elementBeforeStart;
    LinkedListElement* firstElementAfterTemplate = rangeOfTemplate->end->nextElement;

    LinkedListElement* lastElementOfFragment = fragmentList->tail;

    if (!rangeOfTemplate->end->nextElement)
        list->tail = lastElementOfFragment;

    lastElementBeforeTemplate->nextElement = fragmentList->head;
    lastElementOfFragment->nextElement = firstElementAfterTemplate;

    freePartOfList(rangeOfTemplate->start, rangeOfTemplate->end);
    free(rangeOfTemplate);
    return true;
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