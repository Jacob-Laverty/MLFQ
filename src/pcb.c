#include "pcb.h"

void InitPCB(PCB* pcb) {
  pcb->headburst = malloc(sizeof(BurstNode));
  pcb->headburst->burst = malloc(sizeof(Burst));
  pcb->headburst->nextburst = malloc(sizeof(BurstNode));

  pcb->iterator = malloc(sizeof(BurstNode));
  pcb->iterator->burst = malloc(sizeof(Burst));
  pcb->iterator->nextburst = malloc(sizeof(BurstNode));
}
