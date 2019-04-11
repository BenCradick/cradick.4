//
// Created by Ben Cradick on 2019-04-10.
//

#include "PriorityQueue.h"
#include <stdlib.h>

PriorityQueue* priorityQueue(QueueNode* head){
    PriorityQueue* this = malloc(sizeof(PriorityQueue));
    this->queue = queue(head);
    return this;
}