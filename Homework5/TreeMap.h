#ifndef SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_
#define SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_

#include "TreeMap.h"
#include <stdbool.h>
#include <values/values.h>

typedef struct TreeMap TreeMap;
typedef struct TreeMapIterator TreeMapIterator;

typedef struct MapEntry{
    Value key;
    Value value;
} MapEntry;

TreeMap* createTreeMap();

void put(TreeMap* tree, Value key, Value value);

bool hasKey(TreeMap* map, Value key);

Value getLowerBound(TreeMap* map, Value key);

Value getUpperBound(TreeMap* map, Value key);

Value getKey(TreeMapIterator* iterator);

Value getValue(TreeMapIterator* iterator);

MapEntry removeKey(TreeMap* map, Value key);

void deleteTreeMap(TreeMap* tree);

#endif // SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_
