//
// Created by Ben Cradick on 2019-04-10.
//

#ifndef CRADICK_4_PROCESSTABLE_H
#define CRADICK_4_PROCESSTABLE_H

#include <sys/types.h>
struct ProcessTable;

typedef struct ProcessTable{
    key_t process_table_key;
    int process_table_shmid;

    int (*process_table)[8];

    void(*detach)(struct ProcessTable*);
    void(*clean)(struct ProcessTable*);



}ProcessTable;

ProcessTable* processTable();

#endif //CRADICK_4_PROCESSTABLE_H
