//
// Created by Ben Cradick on 2019-04-10.
//

#include "Queues/Queue.h"
#include <stdlib.h>

void __enQueue__(QueueNode *new, Queue *this);
QueueNode* __deQueue__(Queue *this);
int __isEmpty__(Queue *this);

Queue* queue(QueueNode* head){
    Queue* queue = malloc(sizeof(queue));

    queue->first = head;
    queue->last = head;

    queue->enQueue = &__enQueue__;
    queue->deQueue = &__deQueue__;
    queue->isEmpty = &__isEmpty__;


    return queue;
}
void __enQueue__(QueueNode *new, Queue *this){
    this->last->next = new;
    this->last = new;
}
QueueNode* __deQueue__(Queue *this){
    QueueNode* target = this->first;
    this->first = this->first->next;

    return target;
}
int __isEmpty__(Queue *this){
    return this->first == NULL;
}