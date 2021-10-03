#include "dna_editor.h"
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
            if (current2->letter != sequence[i]) {
                isSequence = false;
            }
            current2 = current2->nextElement;
            i++;
        }
        if (isSequence) {
            return current1;
        }
    }
}

LinkedListElement* findLastElementOfSequence(LinkedList* list, const char* sequence)
{
    for (LinkedListElement* current1 = list->head; current1; current1 = current1->nextElement) {
        int i = 0;
        bool isSequence = true;
        LinkedListElement* current2 = current1;
        while (current2 && i < strlen(sequence) && isSequence) {
            if (current2->letter != sequence[i]) {
                isSequence = false;
            }
            current2 = current2->nextElement;
            i++;
        }
        if (isSequence) {
            return current2;
        }
    }
}

void delete (LinkedList* list, const char* start, const char* end)
{
    LinkedListElement* firstElementOfStart = findFirstElementOfSequence(list, start);
    LinkedListElement* lastElementBeforeStart = list->head;
    while (lastElementBeforeStart->nextElement != firstElementOfStart) {
        lastElementBeforeStart = lastElementBeforeStart->nextElement;
    }
    LinkedListElement* firstElementAfterEnd = findLastElementOfSequence(list, end)->nextElement;
    lastElementBeforeStart->nextElement = firstElementAfterEnd;
}

void insert(LinkedList* list, const char* start, const char* fragment)
{
    LinkedListElement* elementBeforeFragment = findLastElementOfSequence(list, start);
    LinkedListElement* elementAfterFragment = elementBeforeFragment->nextElement;
    LinkedList* fragmentList = createLinkedList(fragment);
    elementBeforeFragment->nextElement = fragmentList->head;
    LinkedListElement* lastElementOfFragment = fragmentList->head;
    while (lastElementOfFragment->nextElement) {
        lastElementOfFragment = lastElementOfFragment->nextElement;
    }
    lastElementOfFragment->nextElement = elementAfterFragment;
}

void replace(LinkedList* list, const char* template, const char* fragment)
{
    LinkedList* fragmentList = createLinkedList(fragment);
    LinkedListElement* lastElementBeforeTemplate = list->head;
    LinkedListElement* firstElementOfTemplate = findFirstElementOfSequence(list, template);
    while (lastElementBeforeTemplate->nextElement != firstElementOfTemplate) {
        lastElementBeforeTemplate = lastElementBeforeTemplate->nextElement;
    }
    LinkedListElement* firstElementAfterTemplate = firstElementOfTemplate->nextElement->nextElement;
    LinkedListElement* lastElementOfFragment = fragmentList->head;
    while (lastElementOfFragment->nextElement) {
        lastElementOfFragment = lastElementOfFragment->nextElement;
    }
    lastElementBeforeTemplate->nextElement = fragmentList->head;
    lastElementOfFragment->nextElement = firstElementAfterTemplate;
}

void printList(LinkedList* list)
{
    for (LinkedListElement* current = list->head; current; current = current->nextElement) {
        printf("%c", current->letter);
    }
    printf("\n");
}