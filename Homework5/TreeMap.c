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
};

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
        if (compare(key, node->key) < 0)
            node = node->rightChild;
        else if (compare(key, node->key) > 0)
            node = node->leftChild;
        else
            return true;
    }
    return false;
}

Node* getMaximum(Node* node)
{
    while (node->rightChild)
        node = node->rightChild;
    return node;
}

Node* getMinimum(Node* node)
{
    while (node->leftChild)
        node = node->leftChild;
    return node;
}

Value getLowerBound(TreeMap* map, Value key, bool* thereIsSuchKey)
{
    if (!map->root) {
        thereIsSuchKey = false;
        return key;
    }
    *thereIsSuchKey = true;
    Node* node = map->root;
    Value lowerBound = getMaximum(map->root)->key;
    while (node) {
        if (compare(node->key, key) >= 0) {
            lowerBound = node->key;
            if (!node->leftChild)
                return node->key;
            node = node->leftChild;
        } else {
            if (!node->rightChild) {
                if (compare(lowerBound, key) < 0)
                    *thereIsSuchKey = false;
                return lowerBound;
            }
            node = node->rightChild;
        }
    }
}

Value getUpperBound(TreeMap* map, Value key, bool* thereIsSuchKey)
{
    if (!map->root) {
        thereIsSuchKey = false;
        return key;
    }
    *thereIsSuchKey = true;
    Node* node = map->root;
    Value lowerBound = getMaximum(map->root)->key;
    while (node) {
        if (compare(node->key, key) > 0) {
            lowerBound = node->key;
            if (!node->leftChild)
                return node->key;
            node = node->leftChild;
        } else {
            if (!node->rightChild) {
                if (compare(lowerBound, key) <= 0)
                    *thereIsSuchKey = false;
                return lowerBound;
            }
            node = node->rightChild;
        }
    }
}

Value getKey(TreeMapIterator* iterator)
{
    return iterator->node->key;
}

Value getValue(TreeMapIterator* iterator)
{
    return iterator->node->value;
};

void freeNode(Node* node)
{
    if (node->leftChild)
        freeNode(node->leftChild);
    if (node->rightChild)
        freeNode(node->rightChild);
    free(node);
}

void deleteTreeMap(TreeMap* tree)
{
    if (tree->root)
        freeNode(tree->root);
    free(tree);
}
