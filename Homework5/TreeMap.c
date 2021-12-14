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

Node* find(Node* root, Value key)
{
    if (!root)
        return NULL;
    if (compare(root->key, key) > 0)
        return find(root->leftChild, key);
    else if (compare(root->key, key) < 0)
        return find(root->rightChild, key);
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

void put(TreeMap* tree, Value key, Value value)
{
    if (!tree->root)
        tree->root = insertWithoutBalance(tree->root, key, value);
    else
        insertWithoutBalance(tree->root, key, value);
    tree->root = balance(tree->root);
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

Value get(TreeMap* map, Value key)
{
    Node* node = find(map->root, key);
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

// Возвращает пару из вершины с максимальным ключом и
// корня дерева поиска после удаления этой вершины
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
    Node* node = find(map->root, key);
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

void deleteTreeMap(TreeMap* tree)
{
    if (tree->root)
        freeSubTree(tree->root);
    free(tree);
}
