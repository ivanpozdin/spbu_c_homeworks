#include <priorityQueue/priorityQueue.h>
#include <stdio.h>

int main()
{
    PriorityQueue* queue = makeNewQueue();
    enqueue(wrapInt(10), 1, queue);
    enqueue(wrapInt(50), 2, queue);
    enqueue(wrapInt(40), 4, queue);
    enqueue(wrapInt(60), 3, queue);
    enqueue(wrapInt(80), 15, queue);
    enqueue(wrapInt(100), 9, queue);
    bool hasError = true;
    printf("%i\n", getInt(dequeue(queue, &hasError)));
    printf("%i\n", getInt(dequeue(queue, &hasError)));
    printf("%i\n", getInt(dequeue(queue, &hasError)));
    printf("%i\n", getInt(dequeue(queue, &hasError)));
    printf("%i\n", getInt(dequeue(queue, &hasError)));
    printf("%i\n", getInt(dequeue(queue, &hasError)));
    printf("%i\n", getInt(dequeue(queue, &hasError)));

    deletePriorityQueue(queue);
};
