#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int key;
    struct Node* leftChild;
    struct Node* rightChild;
    int height;
} Node;

struct TreeMap {
    Node* root;
};

Node* createNode(int key, int value)
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

Node* find(Node* root, int key)
{
    if (!root)
        return NULL;
    if (root->key > key)
        return find(root->leftChild, key);
    else if (root->key < key)
        return find(root->rightChild, key);
    return root;
}

Node* insertWithoutBalance(Node* root, int key, int value)
{
    if (!root)
        return createNode(key, value);
    if (root->key > key)
        root->leftChild = insertWithoutBalance(root->leftChild, key, value);
    else if (root->key < key)
        root->rightChild = insertWithoutBalance(root->rightChild, key, value);
    else if (root->key == key)
        root->value = value;
    return root;
}

void put(TreeMap* tree, int key, int value)
{
    if (!tree->root)
        tree->root = insertWithoutBalance(tree->root, key, value);
    else
        insertWithoutBalance(tree->root, key, value);
    tree->root = balance(tree->root);
}

bool hasKey(TreeMap* map, int key)
{
    Node* node = map->root;
    while (node) {
        if (key > node->key)
            node = node->rightChild;
        else if (node->key < key)
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

int getLowerBound(TreeMap* map, int key, bool* thereIsSuchKey)
{
    if (!map->root){
        thereIsSuchKey = false;
        return 0;
    }
    *thereIsSuchKey = true;
    Node* node = map->root;
    int lowerBound = getMaximum(map->root)->key;
    while (node) {
        if (node->key >= key) {
            lowerBound = node->key;
            if (!node->leftChild)
                return node->key;
            node = node->leftChild;
        } else {
            if (!node->rightChild) {
                if (lowerBound < key)
                    *thereIsSuchKey = false;
                return lowerBound;
            }
            node = node->rightChild;
        }
    }
    thereIsSuchKey = false;
    return 0;
}

int getUpperBound(TreeMap* map, int key, bool* thereIsSuchKey)
{
    if (!map->root){
        thereIsSuchKey = false;
        return 0;
    }
    *thereIsSuchKey = true;
    Node* node = map->root;
    int lowerBound = getMaximum(map->root)->key;
    while (node) {
        if (node->key > key) {
            lowerBound = node->key;
            if (!node->leftChild)
                return node->key;
            node = node->leftChild;
        } else {
            if (!node->rightChild) {
                if (lowerBound <= key)
                    *thereIsSuchKey = false;
                return lowerBound;
            }
            node = node->rightChild;
        }
    }
    thereIsSuchKey = false;
    return 0;
}

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

void prettyNodePrint(Node* node, int indent, char indentSymbol, int indentStep)
{
    for (int i = 0; i < indentStep * indent; i++)
        printf("%c", indentSymbol);
    printf("(%d): %d\n", node->key, node->value);
    if (node->leftChild)
        prettyNodePrint(node->leftChild, indent + 1, indentSymbol, indentStep);
    if (node->rightChild)
        prettyNodePrint(node->rightChild, indent + 1, indentSymbol, indentStep);
}

void prettyPrint(TreeMap* tree, char indentSymbol, int indentStep)
{
    if (tree->root) {
        prettyNodePrint(tree->root, 0, indentSymbol, indentStep);
    }
}
