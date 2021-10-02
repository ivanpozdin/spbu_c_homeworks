#include "linked_map.h"

LinkedMapElement* find(LinkedMap* map, const char* key);

struct LinkedMap {
    LinkedMapElement* head;
};

struct LinkedMapElement {
    char key[128];
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
        if (strcmp(current->key, key) == 0) {
            return current;
        }
    }
    return NULL;
}

bool hasKey(LinkedMap* map, const char* key)
{
    if (!find(map, key)) {
        return false;
    }
    return true;
}

int get(struct LinkedMap* map, const char* key)
{
    return find(map, key)->value;
}

void addOne(struct LinkedMap* map, const char* key)
{
    LinkedMapElement* currentElement = find(map, key);
    currentElement->value++;
}

void insertKey(struct LinkedMap* map, const char* key, int maxSizeOfKey)
{
    LinkedMapElement* newElement = malloc(sizeof(LinkedMapElement));
    newElement->nextElement = map->head;
    strcpy_s(newElement->key, maxSizeOfKey, key);
    newElement->value = 1;
    map->head = newElement;
}

void put(LinkedMap* map, const char* key, int maxSizeOfKey)
{
    if (hasKey(map, key)) {
        addOne(map, key);
    } else {
        insertKey(map, key, maxSizeOfKey);
    }
}

void printResultInFile(FILE* outputFile, struct LinkedMap* map)
{
    LinkedMapElement* currentElement = map->head;
    while (currentElement) {
        fprintf(outputFile, "%s %i\n", currentElement->key, currentElement->value);
        currentElement = currentElement->nextElement;
    }
}

void deleteMap(LinkedMap* map)
{
    LinkedMapElement* currentElement = map->head;
    LinkedMapElement* nextElement = NULL;
    while (currentElement != NULL) {
        nextElement = currentElement->nextElement;
        free(currentElement);
        currentElement = nextElement;
    }
    free(map);
}