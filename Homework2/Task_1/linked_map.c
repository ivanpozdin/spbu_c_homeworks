#include "linked_map.h"

struct LinkedMap {
    LinkedMapElement* head;
};

struct LinkedMapElement {
    char key[127];
    int value;
    struct LinkedMapElement* nextElement;
};

LinkedMap* makeNewLinkedMap()
{
    LinkedMap* map = malloc(sizeof(LinkedMap));
    map->head = NULL;
    return map;
}

struct LinkedMapElement* makeNewLinkedMapElement(const char* key, int value)
{
    LinkedMapElement* mapElement = malloc(sizeof(LinkedMapElement));
    strcpy(mapElement->key, key);
    mapElement->value = value;
    mapElement->nextElement = NULL;
    return mapElement;
}

bool hasKey(LinkedMap* map, const char* key)
{
    LinkedMapElement* currentElement = map->head;
    while (currentElement != NULL) {
        if (strcmp(currentElement->key, key) == 0) {
            return true;
        }
        currentElement = currentElement->nextElement;
    }
    return false;
}

int get(struct LinkedMap* map, const char* key)
{
    LinkedMapElement* currentElement = map->head;
    while (currentElement != NULL) {
        if ((strcmp(currentElement->key, key) == 0)) {
            return currentElement->value;
        }
        currentElement = currentElement->nextElement;
    }
}

void addOne(struct LinkedMap* map, const char* key)
{
    LinkedMapElement* currentElement = map->head;
    while (currentElement != NULL) {
        if ((strcmp(currentElement->key, key) == 0)) {
            currentElement->value++;
            break;
        }
        currentElement = currentElement->nextElement;
    }
}

void insertKeyAtTheEnd(struct LinkedMap* map, const char* key)
{
    LinkedMapElement* newElement = malloc(sizeof(LinkedMapElement));
    if (map->head == NULL) {
        map->head = newElement;
    } else {
        LinkedMapElement* currentElement = map->head;
        while (currentElement->nextElement != NULL) {
            currentElement = currentElement->nextElement;
        }
        currentElement->nextElement = newElement;
    }
    strcpy(newElement->key, key);
    newElement->value = 1;
    newElement->nextElement = NULL;
}

void put(LinkedMap* map, const char* word)
{
    if (hasKey(map, word)) {
        addOne(map, word);
    } else {
        insertKeyAtTheEnd(map, word);
    }
}

void printResultInFile(FILE* outputFile, struct LinkedMap* map)
{
    LinkedMapElement* currentElement = map->head;
    while (currentElement != NULL) {
        fprintf(outputFile, "%s %i\n", currentElement->key, currentElement->value);
        currentElement = currentElement->nextElement;
    }
}
