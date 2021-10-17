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
        int lengthOfProcessedSequence = 0;
        int sequenceLength = strlen(sequence);

        for (LinkedListElement* end = start; end; end = end->nextElement) {
            if (end->letter != sequence[lengthOfProcessedSequence])
                break;
            lengthOfProcessedSequence++;

            if (lengthOfProcessedSequence == sequenceLength) {
                range->start = start;
                range->end = end;
                return range;
            }
        }
        range->elementBeforeStart = start;
    }
    return range;
}

bool delete (LinkedList* list, const char* start, const char* end)
{
    ListRange* rangeOfStart = findBordersOfSequence(list->head, start);
    ListRange* rangeOfEnd = findBordersOfSequence(rangeOfStart->end->nextElement, end);

    if (!rangeOfStart->start || !rangeOfEnd->start)
        return false;

    if (!rangeOfEnd->end->nextElement)
        list->tail = rangeOfStart->elementBeforeStart;

    rangeOfStart->elementBeforeStart->nextElement = rangeOfEnd->end->nextElement;

    freePartOfList(rangeOfStart->start, rangeOfEnd->end);
    free(rangeOfStart);
    free(rangeOfEnd);
    return true;
}

bool insert(LinkedList* list, const char* start, const char* fragment)
{
    ListRange* rangeStart = findBordersOfSequence(list->head, start);
    LinkedList* fragmentList = createLinkedListFromSequence(fragment);

    if (!rangeStart->start)
        return false;

    if (!rangeStart->end->nextElement)
        list->tail = fragmentList->tail;

    fragmentList->tail->nextElement = rangeStart->end->nextElement;
    rangeStart->end->nextElement = fragmentList->head;

    free(rangeStart);
    return true;
}

bool replace(LinkedList* list, const char* template, const char* fragment)
{
    LinkedList* fragmentList = createLinkedListFromSequence(fragment);
    ListRange* rangeOfTemplate = findBordersOfSequence(list->head, template);

    if (!rangeOfTemplate->start)
        return false;

    if (!rangeOfTemplate->end->nextElement)
        list->tail = fragmentList->tail;

    rangeOfTemplate->elementBeforeStart->nextElement = fragmentList->head;
    fragmentList->tail->nextElement = rangeOfTemplate->end->nextElement;

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