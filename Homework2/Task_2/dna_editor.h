#ifndef SPBU_C_HOMEWORKS_DNA_EDITOR_H
#define SPBU_C_HOMEWORKS_DNA_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct LinkedList LinkedList;
typedef struct LinkedListElement LinkedListElement;


LinkedList* createLinkedList(const char* sequence);
LinkedListElement* findFirstElementOfSequence(LinkedList* list, const char* sequence);
void replace(LinkedList* list, const char* template,const char* fragment);
void delete(LinkedList* list, const char* start, const char* end);
void insert(LinkedList* list, const char* start,const char* fragment);
void printList(LinkedList* list);
#endif // SPBU_C_HOMEWORKS_DNA_EDITOR_H
