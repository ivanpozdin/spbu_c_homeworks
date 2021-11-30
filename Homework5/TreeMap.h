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

MapEntry removeKey(TreeMap* map, Value key);

Value get(TreeMap* map, Value key);

bool hasKey(TreeMap* map, Value key);



Value getLowerBound(TreeMap* map, Value key);

Value getUpperBound(TreeMap* map, Value key);

Value getMaximum(TreeMap* map);

Value getMinimum(TreeMap* map);

TreeMapIterator* getIterator(TreeMap* map);
Value getKey(TreeMapIterator* iterator);
Value getValue(TreeMapIterator* iterator);
void next(TreeMapIterator* iterator, bool leftChildIsNotUsed);
bool hasElement(TreeMapIterator* iterator);



void deleteTreeMap(TreeMap* tree);

#endif // SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_
