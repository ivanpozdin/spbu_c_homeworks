#ifndef SPBU_C_HOMEWORKS_LIST_H
#define SPBU_C_HOMEWORKS_LIST_H

#include <stdbool.h>


typedef struct LinkedMap LinkedMap;
typedef struct LinkedMapElement LinkedMapElement;


void put(LinkedMap *map, const char *key, int value);
int get(LinkedMap *map, const char *key);
bool hasKey(LinkedMap *map, const char *key);


#endif // SPBU_C_HOMEWORKS_LIST_H
