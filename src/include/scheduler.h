#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "rr_queue.h"
#include "srtf_queue.h"
#include "dd.h"
#include "print_event.h"
#include "stats.h"

typedef struct CPUStateStruct {
  PCB* current_process;
  int allowed_runtime;
  int priority;
} CPUState; 

CPUState* state;
//I'd like to cast these structs to base queue pointer and use func* but I don't have time :/
RRQueue *first_queue;
RRQueue *second_queue;
SRTFQueue *third_queue;

void init_scheduler();
void create_queue(int quantum);
void demote();
void move_cpu_to_io(long time);
void scheduler_tick(long time);
void process_arrival(PCB* process, long time);
#endif
