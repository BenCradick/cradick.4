//
// Created by Ben Cradick on 2019-04-12.
//

#include "MessageQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void sendMessage(const char*, int,long, MessageQueue* );
const char receiveMessage(int message_flag, long flag, struct MessageQueue *this);
void deleteQueue(struct MessageQueue*);
MessageQueue* messageQueue(int id){
    id++; //this needs to happen because this struct will be used in an array whose index will dictate passed value of id
    if(id < 1){
        fprintf(stderr, "MessageQueue* messageQueue(int id): variable id must be > 0");
        exit(EXIT_FAILURE);
    }

    MessageQueue* this = malloc(sizeof(MessageQueue));

    if ((this->message_key = ftok(".", id)) == -1){
        perror("ftok: ");
    }

    if((this->message_id = msgget(this->message_key, PERMS | IPC_CREAT)) == -1){
        perror("msgget: ");
    }

    this->sendMessage = &sendMessage;
    this->receiveMessage = &receiveMessage;
    this->deleteQueue = &deleteQueue;

    return this;

}

typedef struct message_buffer{
    long message_flag;
    char message[1];
}message_buffer;

void sendMessage(const char message[1], int message_flag, long flags, MessageQueue* this){
    message_buffer buffer;
    strncpy(buffer.message, message, 1);
    buffer.message_flag = flags;

    if(msgsnd(this->message_id, &buffer, sizeof(char), message_flag) == -1){
        perror("msgsend: ");
        exit(EXIT_FAILURE);
    }
}
const char receiveMessage(int message_flag, long flag, MessageQueue *this){
    message_buffer buffer;
    buffer.message_flag = flag;

    if(msgrcv(this->message_id, &buffer, sizeof(char), flag, message_flag) == -1){
        perror("msgrcv: ");
        exit(EXIT_FAILURE);
    }
    char* message = buffer.message;
    return *message;
}
void deleteQueue(MessageQueue* this){
    if(msgctl(this->message_id, IPC_RMID, NULL) == -1){
        perror("msgctl: ");
        exit(EXIT_FAILURE);
    }
}
