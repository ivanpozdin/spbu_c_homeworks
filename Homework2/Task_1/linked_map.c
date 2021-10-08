#include "linked_map.h"

LinkedMapElement* find(LinkedMap* map, const char* key);

struct LinkedMap {
    LinkedMapElement* head;
};

struct LinkedMapElement {
    char* key;
    int value;
    struct LinkedMapElement* nextElement;
};

LinkedMap* makeNewLinkedMap()
{
    LinkedMap* map = malloc(sizeof(LinkedMap));
    map->head = NULL;
    return map;
}

LinkedMapElement* find(LinkedMap* map, const char* key)
{
    for (LinkedMapElement* current = map->head; current; current = current->nextElement) {
        if (strcmp(current->key, key) == 0)
            return current;
    }
    return NULL;
}

bool hasKey(LinkedMap* map, const char* key)
{
    return find(map, key);
}

int get(LinkedMap* map, const char* key, int defaultValue)
{
    if (hasKey(map, key))
        return find(map, key)->value;
    return defaultValue;
}

void changeValue(LinkedMap* map, const char* key, int newValue)
{
    LinkedMapElement* currentElement = find(map, key);
    currentElement->value = newValue;
}

void insertKey(LinkedMap* map, const char* key, int value)
{
    LinkedMapElement* newElement = malloc(sizeof(LinkedMapElement));
    newElement->nextElement = map->head;
    newElement->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(newElement->key, key);
    newElement->value = value;
    map->head = newElement;
}

void put(LinkedMap* map, const char* key, int value)
{
    if (hasKey(map, key))
        changeValue(map, key, value);
    else
        insertKey(map, key, value);
}

void printAllKeysAndValues(FILE* outputFile, struct LinkedMap* map, char separator)
{
    for (LinkedMapElement* currentElement = map->head; currentElement; currentElement = currentElement->nextElement) {
        fprintf(outputFile, "%s%c%i\n", currentElement->key, separator, currentElement->value);
    }
}

void deleteMap(LinkedMap* map)
{
    LinkedMapElement* nextElement = NULL;
    for (LinkedMapElement* currentElement = map->head; currentElement; currentElement = nextElement) {
        nextElement = currentElement->nextElement;
        free(currentElement->key);
        free(currentElement);
    }
    free(map);
}
