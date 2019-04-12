//
// Created by Ben Cradick on 2019-04-12.
//

#ifndef CRADICK_4_MESSAGEQUEUE_H
#define CRADICK_4_MESSAGEQUEUE_H

#include <sys/msg.h>

#define PERMS 0666
#define PARENT 202

struct MessageQueue;

typedef struct MessageQueue{
    key_t message_key;
    int message_id;

    void(*sendMessage)(const char*, int, long, struct MessageQueue*);
    const char*(*recieveMessage)(int, long, struct MessageQueue*);
    void(*deleteQueue)(struct MessageQueue*);
}MessageQueue;

MessageQueue* messageQueue(int);

#endif //CRADICK_4_MESSAGEQUEUE_H
