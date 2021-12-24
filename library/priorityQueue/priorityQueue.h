#ifndef SPBU_C_HOMEWORKS_LIBRARY_PRIORITYQUEUE_PRIORITYQUEUE_H_
#define SPBU_C_HOMEWORKS_LIBRARY_PRIORITYQUEUE_PRIORITYQUEUE_H_

#include <stdbool.h>
#include <values/values.h>

typedef struct PriorityQueue PriorityQueue;
typedef struct queueElement queueElement;
typedef struct ListIterator ListIterator;

PriorityQueue* makeNewQueue();

void deletePriorityQueue(PriorityQueue* queue);

void enqueue(Value value, int priority, PriorityQueue* queue);
Value dequeue(PriorityQueue* queue, bool* hasError);

#endif // SPBU_C_HOMEWORKS_LIBRARY_PRIORITYQUEUE_PRIORITYQUEUE_H_
