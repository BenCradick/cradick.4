//
// Created by Ben Cradick on 2019-04-15.
//

#ifndef CRADICK_4_USERVARIABLES_H
#define CRADICK_4_USERVARIABLES_H

#include <Queues/MessageQueue.h>
#include <ProcessTable/ProcessTable.h>
#include "VClock.h"

struct UserVariables;
typedef struct UserVariables{
    int cpu_last_start_sec;
    int cpu_last_start_nano;
    long cpu_last_start_total;

    long cpu_start_total;

    int cpu_time_sec;
    int cpu_time_nano;
    long cpu_time_total;

    int time_slice;

    int start_time_nano;
    int start_time_sec;
    long start_time_total;

    VClock* clock;

    int id;

    MessageQueue* message_queue;
    MessageQueue* blocked_queue;
    MessageQueue* termination_queue;

    ProcessTable* process_table;

    int row_in_table;

    char message;

}UserVariables;
#endif //CRADICK_4_USERVARIABLES_H
