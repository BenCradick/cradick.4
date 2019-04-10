//
// Created by Ben Cradick on 2019-04-09.
//

#include "VClock.h"
#include <stdlib.h>
#include <memory.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>



//referencable function prototypes
void increment(vClock*);
void messageIncrement(vClock*);
void detach(vClock*);
void clean(vClock*);
vClock* init(){
    vClock *clock = malloc(sizeof(vClock));

    clock->nano_key = ftok("oss", 1);
    clock->sec_key = ftok("oss", 2);

    clock->nano_shmid = shmget(clock->nano_key, sizeof(long), 0666 | IPC_CREAT);
    clock->sec_shmid = shmget(clock->sec_key, sizeof(long), 0666 | IPC_CREAT);

    clock->nano = (long*) shmat(clock->nano_shmid, NULL, 0);
    clock->sec = (long*) shmat(clock->sec_shmid, NULL, 0);

    clock->increment  = &increment;
    clock->messageIncrement = &messageIncrement;
    clock->detach = &detach;
    clock->clean = &clean;

    return clock;
}

//increments by 1 sec and [0,1000] nanoseconds as per instructions
void increment(vClock* clock){
    const long BILLION = 1000000000;
    srand((unsigned int)time(0));

    *clock->sec += 1;
    *clock->nano += rand()%1001; //if modulo 1000 then range 0-999

    if(*clock->nano > BILLION){
        long temp = *clock->nano - BILLION;
        *clock->nano = temp;
        *clock->sec += 1;
    }

}
void messageIncrement(vClock* clock){
    const long BILLION = 1000000000;
    srand((unsigned int)time(0));

    *clock->nano += rand()%9900 + 100;

    if(*clock->nano > BILLION){
        long temp = *clock->nano - BILLION;
        *clock->nano = temp;
        *clock->sec += 1;
    }
}
// detaches local clock from shared memory
void detach(vClock* clock){
    shmdt(clock->nano);
    shmdt(clock->sec);
}
// erases the shared memory
void clean(vClock* clock){
    shmctl(clock->nano_shmid, IPC_RMID, NULL);
    shmctl(clock->nano_shmid, IPC_RMID, NULL);
}