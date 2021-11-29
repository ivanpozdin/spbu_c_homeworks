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

Node* findParent(Node* root, Value key)
{
    if (!root)
        return NULL;
    if (compare(root->leftChild->key, key) == 0 || compare(root->rightChild->key, key) == 0)
        return root;
    if (compare(root->key, key) > 0)
        return find(root->leftChild, key);
    else if (compare(root->key, key) < 0)
        return find(root->rightChild, key);
    return NULL;
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

Value getLowerBound(TreeMap* map, Value key)
{
    if (!map->root)
        return wrapNone();

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
                    return wrapNone();
                return lowerBound;
            }
            node = node->rightChild;
        }
    }
}

Value getUpperBound(TreeMap* map, Value key)
{
    if (!map->root)
        return wrapNone();

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
                    return wrapNone();
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
}

void deleteNode(TreeMap* map, Node* node)
{
    Node* parent = findParent(map->root, node->key);
    if (!node->rightChild && !node->leftChild) {
        if (parent) {
            if (compare(parent->key, node->key) > 0)
                parent->leftChild = NULL;
            else
                parent->rightChild = NULL;
        } else
            map->root = NULL;
        free(node);
    } else if (!node->leftChild ^ !node->rightChild) {
        if (parent) {
            if (compare(parent->key, node->key) > 0)
                parent->leftChild = node->leftChild ? node->leftChild : node->rightChild;
            else
                parent->rightChild = node->leftChild ? node->leftChild : node->rightChild;
        } else
            map->root = node->leftChild ? node->leftChild : node->rightChild;

        free(node);

    } else {
        Node* minNodeInRightSubTree = getMinimum(node->rightChild);
        Node* parentOfMinNodeInRightSubTree = findParent(node->rightChild, minNodeInRightSubTree->key);
        if (compare(parentOfMinNodeInRightSubTree->key, minNodeInRightSubTree->key) > 0)
            parentOfMinNodeInRightSubTree->leftChild = NULL;
        else
            parentOfMinNodeInRightSubTree->rightChild = NULL;
        node->key = minNodeInRightSubTree->key;
        node->value = minNodeInRightSubTree->value;
        free(minNodeInRightSubTree);
    }
    balance(map->root);
    updateHeight(map->root);
}

Node* deleteNodeWithoutBalance(Node* root, Value key){
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

MapEntry removeKey(TreeMap* map, Value key)
{
    Node* node = find(map->root, key);
    if (!node)
        return (MapEntry) { wrapNone(), wrapNone() };
    MapEntry mapEntry = (MapEntry) {node->key, node->value};
    //deleteNode(map, node);
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
