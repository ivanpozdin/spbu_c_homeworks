#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    Value value;
    Value key;
    struct Node* leftChild;
    struct Node* rightChild;
    int height;
} Node;

struct TreeMap {
    Node* root;
};

struct TreeMapIterator {
    Node* node;
    TreeMap* map;
};

void deleteNode(TreeMap* map, Node* node);

Node* createNode(Value key, Value value)
{
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->key = key;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->height = 1;
    return node;
}

TreeMap* createTreeMap()
{
    TreeMap* tree = malloc(sizeof(TreeMap));
    tree->root = NULL;
    return tree;
}

int getHeight(Node* root)
{
    return root ? root->height : 0;
}

void updateHeight(Node* root)
{
    if (root)
        root->height = getHeight(root->leftChild) + getHeight(root->rightChild) + 1;
}

Node* rotateLeft(Node* root)
{
    Node* child = root->rightChild;
    root->rightChild = child->leftChild;
    child->leftChild = root;
    updateHeight(root);
    updateHeight(child);
    return child;
}

Node* rotateRight(Node* root)
{
    Node* child = root->leftChild;
    root->leftChild = child->rightChild;
    child->rightChild = root;
    updateHeight(root);
    updateHeight(child);
    return child;
}

int getBalanceFactor(Node* root)
{
    if (!root)
        return 0;
    int left = root->leftChild ? root->leftChild->height : 0;
    int right = root->rightChild ? root->rightChild->height : 0;
    return right - left;
}

Node* balance(Node* root)
{
    if (getBalanceFactor(root) == 2) {
        if (getBalanceFactor(root->rightChild) == -1)
            root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    if (getBalanceFactor(root) == -2) {
        if (getBalanceFactor(root->leftChild) == 1)
            root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }
    return root;
}

Node* findNodeWithGivenKey(Node* root, Value key)
{
    if (!root)
        return NULL;
    if (compare(root->key, key) > 0)
        return findNodeWithGivenKey(root->leftChild, key);
    else if (compare(root->key, key) < 0)
        return findNodeWithGivenKey(root->rightChild, key);
    return root;
}

Node* insertWithoutBalance(Node* root, Value key, Value value)
{
    if (!root)
        return createNode(key, value);
    if (compare(root->key, key) > 0)
        root->leftChild = insertWithoutBalance(root->leftChild, key, value);
    else if (compare(root->key, key) < 0)
        root->rightChild = insertWithoutBalance(root->rightChild, key, value);
    else if (compare(root->key, key) == 0)
        root->value = value;
    return root;
}

void put(TreeMap* map, Value key, Value value)
{
    if (!map->root)
        map->root = insertWithoutBalance(map->root, key, value);
    else
        insertWithoutBalance(map->root, key, value);
    map->root = balance(map->root);
}

bool hasKey(TreeMap* map, Value key)
{
    Node* node = map->root;
    while (node) {
        if (compare(key, node->key) > 0)
            node = node->rightChild;
        else if (compare(key, node->key) < 0)
            node = node->leftChild;
        else
            return true;
    }
    return false;
}

Value getValueFromKey(TreeMap* map, Value key)
{
    Node* node = findNodeWithGivenKey(map->root, key);
    if (node)
        return node->value;
    return wrapNone();
}

Node* getNodeWithMaxKey(Node* node)
{
    while (node && node->rightChild)
        node = node->rightChild;
    return node;
}

Node* getNodeWithMinKey(Node* node)
{
    while (node && node->leftChild)
        node = node->leftChild;
    return node;
}

Value getLowerBound(TreeMap* map, Value key)
{
    Node* node = map->root;
    if (!node)
        return wrapNone();

    Value lowerBound = map->root->key;
    while (node) {
        if (compare(node->key, key) >= 0) {
            lowerBound = node->key;
            node = node->leftChild;
        } else {
            if (!node->rightChild) {
                if (compare(lowerBound, key) >= 0)
                    return lowerBound;
                return wrapNone();
            }
            node = node->rightChild;
        }
    }
    return lowerBound;
}

Value getUpperBound(TreeMap* map, Value key)
{
    if (!map->root)
        return wrapNone();

    Node* node = map->root;
    Value lowerBound = getNodeWithMaxKey(map->root)->key;
    while (node) {
        if (compare(node->key, key) > 0) {
            lowerBound = node->key;
            if (!node->leftChild)
                return node->key;
            node = node->leftChild;
        } else {
            if (!node->rightChild) {
                if (compare(lowerBound, key) <= 0)
                    return wrapNone();
                return lowerBound;
            }
            node = node->rightChild;
        }
    }
    return wrapNone();
}

Value getMaximum(TreeMap* map)
{
    Node* node = getNodeWithMaxKey(map->root);
    if (node)
        return node->key;
    else
        return wrapNone();
}

Value getMinimum(TreeMap* map)
{
    Node* node = getNodeWithMinKey(map->root);
    if (node)
        return node->key;
    else
        return wrapNone();
}

TreeMapIterator* getIterator(TreeMap* map)
{
    TreeMapIterator* iterator = malloc(sizeof(TreeMapIterator));
    iterator->node = map->root;
    iterator->map = map;
    return iterator;
}

Value getKey(TreeMapIterator* iterator)
{
    return iterator->node->key;
}

Value getValue(TreeMapIterator* iterator)
{
    return iterator->node->value;
}

Node* findParent(Node* root, Value key)
{
    if (!root)
        return NULL;
    if (compare(root->leftChild->key, key) == 0 || compare(root->rightChild->key, key) == 0)
        return root;
    if (compare(root->key, key) > 0)
        return findParent(root->leftChild, key);
    else if (compare(root->key, key) < 0)
        return findParent(root->rightChild, key);
    return NULL;
}

bool hasElement(TreeMapIterator* iterator)
{
    return iterator->node != NULL;
}

void next(TreeMapIterator* iterator, bool leftChildIsNotUsed)
{
    if (iterator->node == getNodeWithMaxKey(iterator->map->root)) {
        iterator->node = false;
        return;
    }

    if (iterator->node->leftChild && leftChildIsNotUsed) {
        iterator->node = iterator->node->leftChild;
        return;
    }
    if (iterator->node->rightChild && (!leftChildIsNotUsed && iterator->node->leftChild || leftChildIsNotUsed)) {
        iterator->node = iterator->node->rightChild;
        return;
    }

    iterator->node = findParent(iterator->map->root, iterator->node->key);
    next(iterator, false);
}

typedef struct Pair {
    Node* first;
    Node* second;
} Pair;

Pair makePair(Node* first, Node* second)
{
    return (Pair) { first, second };
}

Pair extractMax(Node* root)
{
    if (root->rightChild) {
        Pair pair = extractMax(root->rightChild);
        root->rightChild = pair.second;
        return makePair(pair.first, root);
    }
    return makePair(root, root->leftChild);
}

Node* deleteNodeWithoutBalance(Node* root, Value key)
{
    if (!root)
        return NULL;
    if (compare(root->key, key) > 0) {
        root->leftChild = deleteNodeWithoutBalance(root->leftChild, key);
        return root;
    } else if (compare(root->key, key) < 0) {
        root->rightChild = deleteNodeWithoutBalance(root->rightChild, key);
        return root;
    }
    Node* newRoot = NULL;
    if (!root->leftChild)
        newRoot = root->rightChild;
    else if (!root->rightChild)
        newRoot = root->leftChild;
    else {
        Pair pair = extractMax(root->leftChild);
        newRoot = pair.first;
        newRoot->leftChild = pair.second;
        newRoot->rightChild = root->rightChild;
    }
    free(root);
    return newRoot;
}

void deleteNode(TreeMap* map, Node* node)
{
    map->root = deleteNodeWithoutBalance(map->root, node->key);
    updateHeight(map->root);
    balance(map->root);
}

MapEntry removeKey(TreeMap* map, Value key)
{
    Node* node = findNodeWithGivenKey(map->root, key);
    if (!node)
        return (MapEntry) { wrapNone(), wrapNone() };
    MapEntry mapEntry = (MapEntry) { node->key, node->value };
    deleteNode(map, node);
    return mapEntry;
}

void freeSubTree(Node* node)
{
    if (node->leftChild)
        freeSubTree(node->leftChild);
    if (node->rightChild)
        freeSubTree(node->rightChild);
    free(node);
}

void deleteTreeMap(TreeMap* map)
{
    if (map->root)
        freeSubTree(map->root);
    free(map);
}

void traverse(Node* root, int* idx, keyValuePair* array)
{
    if (root->leftChild)
        traverse(root->leftChild, idx, array);
    array[*idx].key = root->key;
    array[*idx].value = root->value;
    (*idx)++;
    if (root->rightChild)
        traverse(root->rightChild, idx, array);
}

keyValuePair* getKeysValuesArray(TreeMap* map, int* sizeOfArray)
{
    keyValuePair* array = malloc(sizeof(keyValuePair) * ((1 << getHeight(map->root)) + 1));
    int idx = 0;
    traverse(map->root, &idx, array);
    *sizeOfArray = idx;
    return array;
}
