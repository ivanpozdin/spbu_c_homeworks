#include "priorityQueue.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct PriorityQueue {
    queueElement* head;
};

struct queueElement {
    Value value;
    int priority;
    queueElement* nextElement;
};

PriorityQueue* makeNewQueue()
{
    PriorityQueue* queue = malloc(sizeof(PriorityQueue));
    queue->head = NULL;
    return queue;
}

queueElement* makeNewQueueElement(Value value, int priority)
{
    queueElement* newElement = malloc(sizeof(queueElement));
    newElement->value = value;
    newElement->priority = priority;
    newElement->nextElement = NULL;
    return newElement;
}

void enqueue(Value value, int priority, PriorityQueue* queue)
{
    queueElement* newElement = makeNewQueueElement(value, priority);
    if (queue->head == NULL) {
        queue->head = newElement;
        return;
    }
    queueElement* currentElement = queue->head;
    if (newElement->priority >= queue->head->priority) {
        queueElement* tmpElement = queue->head;
        queue->head = newElement;
        queue->head->nextElement = tmpElement;
        return;
    }
    while (newElement->priority < currentElement->nextElement->priority)
        currentElement = currentElement->nextElement;

    queueElement* afterNewElement = currentElement->nextElement;
    currentElement->nextElement = newElement;
    newElement->nextElement = afterNewElement;
}

Value dequeue(PriorityQueue* queue, bool* hasError)
{
    if (!queue->head) {
        *hasError = true;
        return wrapInt(-1);
    }
    Value valueWithMaxPriority = queue->head->value;
    queue->head = queue->head->nextElement;
    *hasError = false;
    return valueWithMaxPriority;
}

void deletePriorityQueue(PriorityQueue* queue)
{
    queueElement* element = queue->head;
    while (element) {
        queueElement* elementToDelete = element;
        element = element->nextElement;
        free(elementToDelete);
    }
    free(queue);
}
