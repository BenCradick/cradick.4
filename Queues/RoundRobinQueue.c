//
// Created by Ben Cradick on 2019-04-10.
//

#include "Queues/RoundRobinQueue.h"
#include <stdlib.h>
void __enQueue(QueueNode*, RoundRobinQueue*);
QueueNode* __deQueue(RoundRobinQueue *this, int process_pid);

RoundRobinQueue* roundRobinQueue(QueueNode* head, int process_pid){
    RoundRobinQueue* this = malloc(sizeof(RoundRobinQueue));
    this->queue = queue(head);
    this->queue->first->process_pid = process_pid;

    this->enQueue = &__enQueue;
    this->deQueue = &__deQueue;
    return this;

}
void __enQueue(QueueNode*new , RoundRobinQueue* this){
    this->queue->enQueue(new, this->queue);
    this->queue->last->next = this->queue->first;
}
QueueNode* __deQueue(RoundRobinQueue *this, int process_pid){
    if(this->queue->first->process_pid == process_pid){
        return this->queue->deQueue(this->queue);
    }
    QueueNode* temp = this->queue->first;

    while(temp->next->process_pid != process_pid){
        temp = temp->next;
    }
    QueueNode* target = temp->next;
    if(this->queue->first == this->queue->last){
        //if the first node is also last then we return a pointer to that node and set the first and last node to null
        //because when first and last are popped simultaneously then the queue is empty.
        temp = this->queue->first;
        this->queue->first = NULL;
        this->queue->last = NULL;
    }
    else if(temp->next == this->queue->last){
        this->queue->last = temp;
    }
    temp->next = temp->next->next;
    return target;
}