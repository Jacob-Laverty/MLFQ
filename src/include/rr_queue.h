#ifndef RR_QUEUE_H
#define RR_QUEUE_H

#include "pcb.h"

typedef struct RRQueueNodeStruct {
  PCB* process;
  int remaining_quantum;
} RRQueueNode;

typedef struct RRQueueStruct {
  RRQueueNode* head;
  RRQueueNode* tail;
  int quantum;

  void (*push) (struct RRQueueStruct*, PCB*);
  PCB* (*pop) (struct RRQueueStruct*);
  PCB* (*peek) (struct RRQueueStruct*);
} RRQueue; 

RRQueue createRRQueue(int quantum);
#endif
