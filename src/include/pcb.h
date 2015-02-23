#ifndef PCB_H
#define PCB_H

#include "burst.h"

typedef struct PCBStruct {
  int pid;
  int arrivaltime;
  //Burst list
  BurstNode *headburst;
  BurstNode *iterator;
} PCB;

void InitPCB(PCB* p);
#endif
