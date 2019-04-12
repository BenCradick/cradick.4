//
// Created by Ben Cradick on 2019-04-10.
//

#include "ProcessTable.h"
#include <stdlib.h>
#include <memory.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void detach(ProcessTable*);
void clean(ProcessTable*);

ProcessTable* processTable(){
    ProcessTable* table = malloc(sizeof(ProcessTable));

    table->process_table_key = ftok(".", 3);

    table->process_table_shmid = shmget(table->process_table_key, sizeof(int[18][8]), 0666 | IPC_CREAT);

    table->process_table = shmat(table->process_table_shmid, NULL, 0);

    table->detach = &detach;
    table->clean = &clean;

    return table;
}

void detach(ProcessTable* table){
    shmdt(table->process_table);
}
void clean(ProcessTable* table){
    shmctl(table->process_table_shmid, IPC_RMID, NULL);
}

