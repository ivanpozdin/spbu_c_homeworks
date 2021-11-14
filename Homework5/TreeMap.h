#ifndef SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_
#define SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_

#include <stdbool.h>
#include "TreeMap.h"

typedef struct TreeMap TreeMap;

TreeMap* createTreeMap();

void put(TreeMap* tree, int key, int value);

bool hasKey(TreeMap* map, int key);

int getLowerBound(TreeMap* map, int key, bool* thereIsSuchKey);

int getUpperBound(TreeMap* map, int key, bool* thereIsSuchKey);

void deleteTreeMap(TreeMap* tree);

void prettyPrint(TreeMap* tree, char indentSymbol, int indentStep);

#endif // SPBU_C_HOMEWORKS_HOMEWORK5_TREEMAP_H_
