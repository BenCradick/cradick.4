#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include "UserVariables.h"
#include "ProcessTable/TableColumns.h"

//
// Created by Ben Cradick on 2019-04-13.
//



//Function prototypes
int randomTerminator();
int getRowInProcessTable(int, ProcessTable*);
int getTimeSlice(int, ProcessTable*);

long nanoTotal(int sec, int nano);
void terminationBehavior(UserVariables*);
void immediateTermination(UserVariables*);
void normalTermination(UserVariables*);
void awaitEvent(UserVariables*);
void preemptiveTermination(UserVariables*);
void updateTable(UserVariables*);


//main mostly serves to initialize key variables.
int main(int argc, char** argv){

    UserVariables variables;
    if((variables.id = (int)strtol(argv[1],NULL, 10)) < 0){
        fprintf(stderr, "UserProcess: Invalid 1st argument\n");
        exit(EXIT_FAILURE);
    }
    srand(time(0));

    variables.clock = vClock();

    variables.start_time_sec = *variables.clock->sec;
    variables.start_time_nano = *variables.clock->nano;
    variables.start_time_total = variables.clock->total(variables.clock);

    variables.cpu_time_sec = 0;
    variables.cpu_time_nano = 0;

    variables.message_queue = messageQueue(variables.id);
    variables.blocked_queue = messageQueue(BLOCKED);
    variables.termination_queue = messageQueue(TERMINATION);

    variables.process_table = processTable();

    // a very large number of the values in variables  above must be initialized after this line, otherwise they would be
    //absent from the process table
    variables.message = variables.message_queue->receiveMessage(0,0, variables.message_queue);

    if(variables.message != 'g'){
        //TODO: Respond to this unexpected event, report to parent.

        fprintf(stderr, "UserProcess: Unexpected command given on launch of process with id %d\n", variables.id);
        variables.process_table->detach(variables.process_table);
        exit(EXIT_FAILURE);
    }

    variables.cpu_last_start_total = variables.clock->total(variables.clock);


    variables.row_in_table = getRowInProcessTable(variables.id, variables.process_table);
    variables.time_slice = getTimeSlice(variables.row_in_table, variables.process_table);

    terminationBehavior(&variables);




}
void terminationBehavior(UserVariables* variables){
    switch(randomTerminator()){
        case 0:
            immediateTermination(variables);
        case 1:
            normalTermination(variables);
        case 2:
            awaitEvent(variables);
        case 3:
            preemptiveTermination(variables);
        default:
            fprintf(stderr, "UserProcess: Invalid number generated\n");
            exit(EXIT_FAILURE);

    }
}
void immediateTermination(UserVariables* variables){


    //Immediate termination was to take up a random amount of its allotted time slice before actual termination
    variables->time_slice *= ((rand()%99 + 1) / 100); //random percent of it's time slice

    normalTermination(variables);



}
void awaitEvent(UserVariables* variables){
    variables->cpu_last_start_total = variables->clock->total(variables->clock);



    char* message = malloc(sizeof(char));

    long event_end_total;

    int event_end_sec = rand()%6 + variables->cpu_last_start_sec;
    int event_end_nano = ((rand()%1001 / 10000) * BILLION) + variables->cpu_last_start_nano;

    if (event_end_nano > BILLION){
        event_end_sec += event_end_nano/BILLION;
        event_end_nano %= BILLION;
    }

    event_end_total = nanoTotal(event_end_sec, event_end_nano);
    variables->cpu_last_start_total = nanoTotal(variables->cpu_last_start_sec, variables->cpu_last_start_nano);

    long time_slice_end_total = variables->cpu_last_start_total + variables->time_slice;
    for(;;){
        if(event_end_total < variables->clock->total(variables->clock)){

            updateTable(variables);

            sprintf(message, "%d", variables->row_in_table);

            variables->termination_queue->sendMessage(message, 0, 0, variables->termination_queue);
            variables->process_table->detach(variables->process_table);

            exit(EXIT_SUCCESS);
        }
        else if(time_slice_end_total < variables->clock->total(variables->clock)){
            updateTable(variables);

            sprintf(message, "%d", variables->row_in_table);

            variables->blocked_queue->sendMessage(message, 0, 0, variables->blocked_queue);
            variables->message = variables->message_queue->receiveMessage(0,0, variables->message_queue);

            if(variables->message != 'g'){
                fprintf(stderr, "Unknown message type %s\n", &variables->message);
                exit(EXIT_FAILURE);
            }

            variables->cpu_last_start_total = variables->clock->total(variables->clock);


            variables->row_in_table = getRowInProcessTable(variables->id, variables->process_table);
            variables->time_slice = getTimeSlice(variables->row_in_table, variables->process_table);
        }

    }



}
void normalTermination(UserVariables* variables){
    int end_time_nano = variables->time_slice + variables->cpu_last_start_nano;
    int end_time_sec = variables->cpu_last_start_sec + (end_time_nano/BILLION);
    long end_time_total = nanoTotal(end_time_sec, end_time_nano);


    do{
        variables->cpu_time_total = variables->clock->total(variables->clock) - variables->cpu_last_start_total;
    }while(variables->cpu_time_total < end_time_total);

    variables->process_table->process_table[variables->row_in_table][time_in_system_nano] =
            (int)((variables->clock->total(variables->clock) - variables->start_time_total) % BILLION);

    variables->process_table->process_table[variables->row_in_table][time_in_system_sec] =
            (int)((variables->clock->total(variables->clock) - variables->start_time_total) / BILLION);

    //used end_time_sec over variables->cpu_time_* because it more accurately simulates a real OS
    variables->process_table->process_table[variables->row_in_table][total_cpu_time_nano] =
            variables->time_slice%BILLION;

    variables->process_table->process_table[variables->row_in_table][total_cpu_time_sec] =
            variables->time_slice/BILLION;

    variables->process_table->process_table[variables->row_in_table][last_burst_nano] = variables->time_slice%BILLION;
    variables->process_table->process_table[variables->row_in_table][last_burst_sec] = variables->time_slice/BILLION;

    char* temp = malloc(sizeof(char));
    sprintf(temp, "%d", variables->row_in_table);

    variables->termination_queue->sendMessage(temp, 0, 0, variables->termination_queue);
    variables->process_table->detach(variables->process_table);

    exit(EXIT_SUCCESS);
}
int getTimeSlice(int row, ProcessTable* table){
    /*
     * QUANTUM is the baseline time slice defined in VClock.h  1E+7
     * priority in table is an integer corresponding to the index of the priority queue
     * additionally shifting the integer 1 left 1 bit is equivalent to exponentiation by 2.
     * So 1<<(index_of_priority_queue) === 2^(index_of_priority_queue)
     */
    return QUANTUM * 1<<table->process_table[row][priority];
}

int randomTerminator(){


    switch (rand()%100){
        case 0 ... 3:
            return 0;
        case 4 ... 35:
            return 1;
        case 36 ... 67:
            return 2;
        case 68 ... 99:
            return 3;
        default:
            fprintf(stderr, "UserProcess: Invalid number generated.\n");
            exit(EXIT_FAILURE);
    }
}
int getRowInProcessTable(int id, ProcessTable* table){
    for(int i = 0; i < 18; i++){
        if(table->process_table[i][pid] == id){
            return i;
        }
    }
    fprintf(stderr, "UserProcess: Process not found in the process table\n");
    exit(EXIT_FAILURE);
}
long nanoTotal(int sec, int nano){
    sec *= BILLION;
    return nano + sec;
}

void updateTable(UserVariables* variables){
    variables->cpu_time_total += variables->clock->total(variables->clock) - variables->cpu_last_start_total;

    variables->process_table->process_table[variables->row_in_table][time_in_system_nano] =
            (int)(((variables->clock->total(variables->clock) - variables->start_time_total))%BILLION);

    variables->process_table->process_table[variables->row_in_table][time_in_system_sec] =
            (int)(((variables->clock->total(variables->clock) - variables->start_time_total))/BILLION);

    variables->process_table->process_table[variables->row_in_table][total_cpu_time_nano] =
            (int)(variables->cpu_time_total % BILLION);

    variables->process_table->process_table[variables->row_in_table][total_cpu_time_sec] =
            (int)(variables->cpu_time_total / BILLION);

    variables->process_table->process_table[variables->row_in_table][last_burst_nano] =
            (int)(((variables->clock->total(variables->clock) - variables->cpu_last_start_total))%BILLION);

    variables->process_table->process_table[variables->row_in_table][last_burst_sec] =
            (int)(((variables->clock->total(variables->clock) - variables->cpu_last_start_total))/BILLION);
}