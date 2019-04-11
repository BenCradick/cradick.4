//
// Created by Ben Cradick on 2019-04-10.
//

#include "Queues/Queue.h"
#include <stdlib.h>

Queue* queue(QueueNode* head){
    Queue* queue = malloc(sizeof(queue));
    queue->first = head;
    queue->last = head;
    return queue;
}