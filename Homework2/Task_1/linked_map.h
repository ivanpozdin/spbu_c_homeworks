#ifndef SPBU_C_HOMEWORKS_LIST_H
#define SPBU_C_HOMEWORKS_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct LinkedMap LinkedMap;
typedef struct LinkedMapElement LinkedMapElement;

LinkedMap* makeNewLinkedMap();
void put(LinkedMap* map, const char* word, int maxSizeOfKey);
int get(LinkedMap* map, const char* key);
void printResultInFile(FILE* outputFile, struct LinkedMap* map);
void deleteMap(LinkedMap* map);
#endif // SPBU_C_HOMEWORKS_LIST_H