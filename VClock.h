//
// Created by Ben Cradick on 2019-04-09.
//

#ifndef CRADICK_4_VCLOCK_H
#define CRADICK_4_VCLOCK_H

#include <ntsid.h>

struct vClock;

typedef struct vClock {
    // sec short for second, nano is nano second
    key_t nano_key;
    key_t sec_key;

    int nano_shmid;
    int sec_shmid;

    long* nano;
    long* sec;

    void(*increment)(struct vClock*);
    void(*messageIncrement)(struct vClock*);
    void(*detach)(struct vClock*);
    void(*clean)(struct vClock*);

}vClock;

vClock* init();
#endif //CRADICK_4_VCLOCK_H
