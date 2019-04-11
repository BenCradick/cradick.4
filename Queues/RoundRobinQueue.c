//
// Created by Ben Cradick on 2019-04-10.
//

#include "Queues/RoundRobinQueue.h"
#include <stdlib.h>
RoundRobinQueue* roundRobinQueue(QueueNode* head){
    RoundRobinQueue* this = malloc(sizeof(RoundRobinQueue));
    this->queue = queue(head);
    return this;

}