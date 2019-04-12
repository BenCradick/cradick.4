#include <stdio.h>
#include <stdlib.h>
#include "cradick.4.h"

int main() {
    unsigned int block = 0;
    const long QUANTUM = 10000000; // OF SOLACE

    const int MAX_NEW_PROCESS_INTERVAL_NANO;
    const int MAX_NEW_PROCESS_INTERVAL_SEC;

    int total_processes = 0;


    MessageQueue* messageQueues = malloc(sizeof(MessageQueue)*100);

    ProcessTable* process_table = processTable();

    VClock* clock = vClock();

    return 0;
}