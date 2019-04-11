//
// Created by Ben Cradick on 2019-04-10.
//

#include "Queues/RoundRobinQueue.h"
#include <stdlib.h>
void enQueue(QueueNode*, RoundRobinQueue*);
QueueNode* deQueue(RoundRobinQueue*, int);
RoundRobinQueue* roundRobinQueue(QueueNode* head, int process_pid){
    RoundRobinQueue* this = malloc(sizeof(RoundRobinQueue));
    this->queue = queue(head);
    this->queue->first->process_pid = process_pid;

    this->enQueue = &enQueue;
    this->deQueue = &deQueue;
    return this;

}
void enQueue(QueueNode* new, RoundRobinQueue* this){
    this->queue->enQueue(new, this->queue);
    this->queue->last->next = this->queue->first;
}
QueueNode* deQueue(RoundRobinQueue* this, int process_pid){
    if(this->queue->first->process_pid == process_pid){
        return this->queue->deQueue(this->queue);
    }
    QueueNode* temp = this->queue->first;

    while(temp->next->process_pid != process_pid){
        temp = temp->next;
    }
    QueueNode* target = temp->next;
    if(temp->next == this->queue->last){
        this->queue->last = temp;
    }
    temp->next = temp->next->next;
    return target;
}