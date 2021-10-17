#ifndef SPBU_C_HOMEWORKS_DNA_EDITOR_H
#define SPBU_C_HOMEWORKS_DNA_EDITOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList LinkedList;
typedef struct LinkedListElement LinkedListElement;

LinkedList* createLinkedListFromSequence(const char* sequence);
bool replace(LinkedList* list, const char* template, const char* fragment);
bool delete (LinkedList* list, const char* start, const char* end);
bool insert(LinkedList* list, const char* start, const char* fragment);
void printList(FILE* outputFile, LinkedList* list);
void freeList(LinkedList* list);

#endif // SPBU_C_HOMEWORKS_DNA_EDITOR_H
