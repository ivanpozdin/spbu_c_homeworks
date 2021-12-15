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
void putKeyInLinkedMap(LinkedMap* map, const char* key, int value);
int getValueFromKeyInLinkedMap(LinkedMap* map, const char* key, int defaultValue);
void printAllKeysAndValues(FILE* outputFile, struct LinkedMap* map, char separator);
void deleteLinkedMap(LinkedMap* map);
bool hasKeyInLinkedMap(LinkedMap* map, const char* key);
#endif // SPBU_C_HOMEWORKS_LIST_H