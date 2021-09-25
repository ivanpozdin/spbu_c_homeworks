#include "linked_map.h"
#include <printf.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct LinkedMap{
    LinkedMapElement* head;
    LinkedMapElement* tail;
    int LinkedMapSize;
};

struct LinkedMapElement{
    const char* key;
    int value;
    struct LinkedMapElement* nextElement;
};

LinkedMap* makeNewLinkedMap(){
    LinkedMap* map = malloc(sizeof(LinkedMap));
    map->head = NULL;
    map->tail = NULL;
    map->LinkedMapSize = 0;
    return map;
}

int get(LinkedMap *map, const char *key){
    LinkedMapElement* currentElement = map->head;
    while(currentElement != NULL){
        if (currentElement->key == key){
            return currentElement->value;
        }
        currentElement = currentElement->nextElement;
    }
}

bool hasKey(LinkedMap *map, const char *key){
    LinkedMapElement* currentElement = map->head;
    while(currentElement != NULL){
        if (currentElement->key == key){
            return true;
        }
        currentElement = currentElement->nextElement;
    }
    return false;
}

void put(LinkedMap *map, const char *key, int value){
    LinkedMapElement* newElement = malloc(sizeof(LinkedMapElement));
    newElement->key = key;
    newElement->value = value;
    newElement->nextElement = NULL;
}