#include "rr_queue.h"

void rr_push(RRQueue* queue, PCB* process) {
 printf("Pushing a thing onto the RRQueue\n");
}

PCB* rr_pop(RRQueue* queue) {
  printf("Popping a thing off the RRQueue\n");
}

PCB* rr_peek(RRQueue* queue) {
  printf("Peeking at a thing on the RRQueue\n");
}


RRQueue createRRQueue(int quantum) {
  RRQueue queue; 
  queue.head = NULL;
  queue.tail = NULL;
  queue.quantum = quantum;
  queue.push = &rr_push;
  queue.pop = &rr_pop;
  queue.peek = &rr_peek;

  return queue;
}
