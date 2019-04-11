//
// Created by Ben Cradick on 2019-04-10.
//


#ifndef CRADICK_4_PRIORITYQUEUE_H
#define CRADICK_4_PRIORITYQUEUE_H


#include "Queue.h"

typedef struct PriorityQueue{

    Queue* queue;

    void(*enQueue)(struct QueueNode*, struct PriorityQueue*);

    QueueNode* (*deQueue)(struct PriorityQueue*);

}PriorityQueue;

PriorityQueue* priorityQueue(QueueNode*);

#endif //CRADICK_4_PRIORITYQUEUE_H
