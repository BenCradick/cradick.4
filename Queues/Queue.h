//
// Created by Ben Cradick on 2019-04-10.
//

#ifndef CRADICK_4_QUEUE_H
#define CRADICK_4_QUEUE_H

#include "Queues/QueueNode.h"

struct Queue;
typedef struct Queue{
    QueueNode* first;
    QueueNode* last;

    void (*enQueue)(struct QueueNode*, struct Queue*);
    QueueNode* (*deQueue)(struct Queue*);

} Queue;
Queue* queue(QueueNode*);

#endif //CRADICK_4_QUEUE_H
