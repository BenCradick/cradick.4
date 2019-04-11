//
// Created by Ben Cradick on 2019-04-10.
//

#ifndef CRADICK_4_QUEUENODE_H
#define CRADICK_4_QUEUENODE_H
struct QueueNode;

typedef struct QueueNode{

    int process_pid;

    struct QueueNode *next;

}QueueNode;

#endif //CRADICK_4_QUEUENODE_H
