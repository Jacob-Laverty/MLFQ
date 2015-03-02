#ifndef RR_QUEUE_H
#define RR_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"

typedef struct RRQueueNodeStruct {
  PCB* process;
  int remaining_quantum;
  struct RRQueueNodeStruct* next;
} RRQueueNode;

typedef struct RRQueueStruct {
  RRQueueNode* head;
  RRQueueNode* tail;
  int quantum;
  int size;

  void (*wait) (struct RRQueueStruct*);
  int (*get_quantum) (struct RRQueueStruct*);
  void (*push) (struct RRQueueStruct*, PCB*);
  PCB* (*pop) (struct RRQueueStruct*);
  PCB* (*peek) (struct RRQueueStruct*);
} RRQueue; 

void rr_wait(RRQueue* queue);
void createRRQueue(RRQueue** queue, int quantum);
void print_rr_queue(RRQueue* queue, FILE* file);
#endif
