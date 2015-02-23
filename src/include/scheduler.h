#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "rr_queue.h"
#include "srtf_queue.h"

//I hate this
//I'd like to inherit structs and use func* but I don't have time :/
RRQueue first_queue;
RRQueue second_queue;
SRTFQueue third_queue;

void createQueue(int quantum);

void testQueues();
#endif
