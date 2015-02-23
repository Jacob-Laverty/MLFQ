#ifndef SRTF_QUEUE_H
#define SRTF_QUEUE_H

#include "pcb.h"

typedef struct SRTFQueueNodeStruct {
  PCB* process;
} SRTFQueueNode;

typedef struct SRTFQueueStruct {
  SRTFQueueNode* head;
  SRTFQueueNode* tail;

  void (*push) (struct SRTFQueueStruct*, PCB*);
  PCB* (*pop) (struct SRTFQueueStruct*);
  PCB* (*peek) (struct SRTFQueueStruct*);
} SRTFQueue; 

SRTFQueue createSRTFQueue();

#endif
