//
// Created by Ben Cradick on 2019-04-10.
//

#include "Queues/Queue.h"
#include <stdlib.h>
void enQueue(QueueNode*, Queue*);
QueueNode* deQueue(Queue*);
Queue* queue(QueueNode* head){
    Queue* queue = malloc(sizeof(queue));
    queue->first = head;
    queue->last = head;
    queue->enQueue = &enQueue;
    queue->deQueue = &deQueue;


    return queue;
}
void enQueue(QueueNode* new, Queue* this){
    this->last->next = new;
    this->last = new;
}
QueueNode* deQueue(Queue* this){
    QueueNode* target = this->first;
    this->first = this->first->next;

    return target;
}