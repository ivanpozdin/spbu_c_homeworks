#ifndef SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_
#define SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_

#include "TreeMap.h"
#include <stdbool.h>
#include <values/values.h>

typedef struct TreeMap TreeMap;
typedef struct TreeMapIterator TreeMapIterator;

TreeMap* createTreeMap();

void put(TreeMap* tree, Value key, Value value);

bool hasKey(TreeMap* map, Value key);

Value getLowerBound(TreeMap* map, Value key, bool* thereIsSuchKey);

Value getUpperBound(TreeMap* map, Value key, bool* thereIsSuchKey);

Value getKey(TreeMapIterator* iterator);

Value getValue(TreeMapIterator* iterator);

void deleteTreeMap(TreeMap* tree);

#endif // SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_
