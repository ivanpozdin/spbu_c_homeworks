#include "doubly_linked_list.h"
#include <printf.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct List {
    ListElement* head;
    ListElement* tail;
    int listSize;
};

struct ListElement {
    int data;
    ListElement* nextElement;
    ListElement* previousElement;
};

struct ListIterator {
    ListElement* element;
};

List* makeNewList()
{
    List* lst = malloc(sizeof(List));
    lst->head = NULL;
    lst->tail = NULL;
    lst->listSize = 0;
    return lst;
}

ListElement* makeNewListElement(int data)
{
    ListElement* newElement = malloc(sizeof(ListElement));
    newElement->data = data;
    newElement->nextElement = NULL;
    newElement->previousElement = NULL;
    return newElement;
}

bool insert(int data, int position, List* list)
{
    if (position > list->listSize)
        return false;

    ListElement* currentElement = makeNewListElement(data);
    if (list->head == NULL) {
        if (position == 0) {
            list->head = currentElement;
            list->tail = currentElement;
            list->listSize++;
            return true;
        } else {
            return false;
        }
    }

    list->listSize++;

    if (position == 0) {
        currentElement->nextElement = list->head;
        list->head->previousElement = currentElement;
        list->head = currentElement;
        return true;
    }

    if (position == list->listSize - 1) {
        list->tail->nextElement = currentElement;
        currentElement->previousElement = list->tail;
        list->tail = currentElement;
        return true;
    }

    ListElement* elementBefore = list->head;
    for (int i = 0; i < position - 1; ++i)
        elementBefore = elementBefore->nextElement;

    ListElement* elementAfter = elementBefore->nextElement;
    elementBefore->nextElement = currentElement;
    currentElement->previousElement = elementBefore;
    currentElement->nextElement = elementAfter;
    elementAfter->previousElement = currentElement;

    return true;
}

bool locate(int data, List* l, int* position)
{
    int index = 0;
    ListElement* currentElement = l->head;
    while (currentElement != NULL) {
        if (currentElement->data == data) {
            *position = index;
            return true;
        }

        index++;
        currentElement = currentElement->nextElement;
    }
    return false;
}

int getListSize(List* lst)
{
    return lst->listSize;
}

void printList(List* lst)
{
    if (lst->head == NULL) {
        printf("List is empty\n");
    }
    ListElement* currentElement = lst->head;
    while (currentElement != NULL) {
        printf("%d", currentElement->data);
        if (currentElement->nextElement)
            printf(" -> ");

        currentElement = currentElement->nextElement;
    }
    printf("\n");
}

void deleteList(List* list)
{
    ListElement* element = list->head;
    while (element) {
        ListElement* elementToDelete = element;
        element = element->nextElement;
        free(elementToDelete);
    }
    free(list);
}
ListIterator* makeIteratorFromHead(List* list)
{
    ListIterator* iterator = malloc(sizeof(ListIterator));
    iterator->element = list->head;
    return iterator;
}

ListIterator* makeIteratorFromTail(List* list)
{
    ListIterator* iterator = malloc(sizeof(ListIterator));
    iterator->element = list->tail;
    return iterator;
}

bool nextIterator(ListIterator* iterator)
{
    if (!iterator->element)
        return false;
    iterator->element = iterator->element->nextElement;
}

bool previousIterator(ListIterator* iterator)
{
    if (!iterator->element)
        return false;
    iterator->element = iterator->element->previousElement;
}

bool isValidIterator(ListIterator* iterator)
{
    return iterator->element != NULL;
}

int iteratorData(ListIterator* iterator)
{
    return iterator->element->data;
}

void deleteIterator(ListIterator* iterator)
{
    free(iterator);
}
