#ifndef PCB_H
#define PCB_H

#include "burst.h"

typedef struct PCBStruct {
  int pid;
  int arrivaltime;
  int state;

  int waittime;
  //Burst list
  BurstNode *headburst;
  BurstNode *tailburst;
  int burst_queue_size;

  int (*get_remaining_burst) (struct PCBStruct*);
  void (*push) (struct PCBStruct*, Burst*);
  Burst* (*pop) (struct PCBStruct*);
  Burst* (*peek) (struct PCBStruct*);
} PCB;

void InitPCB(PCB** p);
int get_remaining_burst(PCB* process);
void burst_queue_push(PCB* process, Burst* burst);
Burst* burst_queue_pop(PCB* process);
Burst* burst_queue_peek(PCB* process);
#endif
