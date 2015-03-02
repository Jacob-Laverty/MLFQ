#ifndef SRTF_QUEUE_H
#define SRTF_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"

typedef struct SRTFQueueNodeStruct {
  PCB* process;
  int remaining_time;
  struct SRTFQueueNodeStruct* next;
} SRTFQueueNode;

typedef struct SRTFQueueStruct {
  SRTFQueueNode* head;
  SRTFQueueNode* tail;
  int size;

  void (*wait) (struct SRTFQueueStruct*);
  int (*get_srtf) (struct SRTFQueueStruct*);
  void (*push) (struct SRTFQueueStruct*, PCB*);
  PCB* (*pop) (struct SRTFQueueStruct*);
  PCB* (*peek) (struct SRTFQueueStruct*);
} SRTFQueue; 

void srtf_wait(SRTFQueue* queue);
void createSRTFQueue();
void print_srtf_queue(SRTFQueue* queue, FILE* out);

#endif
