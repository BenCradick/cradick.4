//
// Created by Ben Cradick on 2019-04-09.
//

#ifndef CRADICK_4_VCLOCK_H
#define CRADICK_4_VCLOCK_H


#include <sys/types.h>
struct VClock;

typedef struct VClock {
    // sec short for second, nano is nano second
    key_t nano_key;
    key_t sec_key;

    int nano_shmid;
    int sec_shmid;

    long* nano;
    long* sec;

    void(*increment)(struct VClock*);
    void(*messageIncrement)(struct VClock*);
    void(*detach)(struct VClock*);
    void(*clean)(struct VClock*);

}VClock;

VClock* vClock();
#endif //CRADICK_4_VCLOCK_H
