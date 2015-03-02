#include "pcb.h"

int get_remaining_burst(PCB* process) {
  return process->headburst->burst->duration;
}

void burst_queue_push(PCB* process, Burst* burst) {
  BurstNode* b = malloc(sizeof(BurstNode));
  b -> burst = burst;
  b -> nextburst = NULL;
  if(process->headburst == NULL) {
    process -> headburst = b;
  } else {
    process -> tailburst -> nextburst = b;
  }
  process -> tailburst = b;
  process -> burst_queue_size++;
}

Burst* burst_queue_pop(PCB* process) {
  BurstNode* temp = process -> headburst;
  Burst* burst = temp->burst;
  process -> headburst = temp -> nextburst;
  process -> burst_queue_size--;
  free(temp);
  return burst;
}

Burst* burst_queue_peek(PCB* process) {
  if(process -> headburst != NULL) {
    return process -> headburst -> burst;
  }
  return NULL;
}

void InitPCB(PCB** pcb) {
  (*pcb)->get_remaining_burst = &get_remaining_burst;
  (*pcb)->burst_queue_size = 0;
  (*pcb)->headburst = NULL;
  (*pcb)->tailburst = NULL;
  (*pcb)->push = &burst_queue_push;
  (*pcb)->pop = &burst_queue_pop;
  (*pcb)->peek = &burst_queue_peek;
}
