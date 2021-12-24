#ifndef SPBU_C_HOMEWORKS_LIBRARY_DOUBLYLINKEDLIST_DOUBLY_LINKED_LIST_H_
#define SPBU_C_HOMEWORKS_LIBRARY_DOUBLYLINKEDLIST_DOUBLY_LINKED_LIST_H_

#include <stdbool.h>

typedef struct List List;
typedef struct ListElement ListElement;
typedef struct ListIterator ListIterator;

List* makeNewList();

bool insert(int data, int position, List* list);
bool locate(int data, List* l, int* position);

int getListSize(List* l);
void printList(List* lst);
void deleteList(List* list);

ListIterator* makeIteratorFromHead(List* list);
ListIterator* makeIteratorFromTail(List* list);

bool nextIterator(ListIterator* iterator);

bool previousIterator(ListIterator* iterator);

bool isValidIterator(ListIterator* iterator);

int iteratorData(ListIterator* iterator);
void deleteIterator(ListIterator* iterator);

#endif // SPBU_C_HOMEWORKS_LIBRARY_DOUBLYLINKEDLIST_DOUBLY_LINKED_LIST_H_
