//
// Created by Ben Cradick on 2019-04-10.
//

#include "PriorityQueue.h"
#include <stdlib.h>
void enQueue(QueueNode*, PriorityQueue*);
QueueNode* deQueue(PriorityQueue*);
PriorityQueue* priorityQueue(QueueNode* head){
    PriorityQueue* this = malloc(sizeof(PriorityQueue));
    this->queue = queue(head);

    this->enQueue = &enQueue;
    this->deQueue = &deQueue;

    return this;
}
void enQueue(QueueNode* new, PriorityQueue* this){
    this->queue->enQueue(new, this->queue);
}

QueueNode* deQueue(PriorityQueue* this){
    QueueNode* target = this->deQueue(this);
    return target;
}