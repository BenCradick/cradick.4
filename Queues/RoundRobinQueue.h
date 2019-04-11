//
// Created by Ben Cradick on 2019-04-10.
//

#ifndef CRADICK_4_ROUNDROBINQUEUE_H
#define CRADICK_4_ROUNDROBINQUEUE_H

#include "Queue.h"

typedef struct RoundRobinQueue{
    Queue* queue;


    void(*enQueue)(QueueNode*, struct RoundRobinQueue*);

    QueueNode*(*deQueue)(struct RoundRobinQueue*, int);

}RoundRobinQueue;
RoundRobinQueue* roundRobinQueue(QueueNode*,  int);
#endif //CRADICK_4_ROUNDROBINQUEUE_H
