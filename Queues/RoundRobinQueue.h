//
// Created by Ben Cradick on 2019-04-10.
//

#ifndef CRADICK_4_ROUNDROBINQUEUE_H
#define CRADICK_4_ROUNDROBINQUEUE_H

#include "Queue.h"

typedef struct RoundRobinQueue{
    Queue* queue;
}RoundRobinQueue;
RoundRobinQueue* roundRobinQueue();
#endif //CRADICK_4_ROUNDROBINQUEUE_H
