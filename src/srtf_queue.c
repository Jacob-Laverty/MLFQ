#include "srtf_queue.h"

void srtf_push(SRTFQueue* queue, PCB* process) {
 printf("Pushing a thing onto the SRTFQueue\n");
}

PCB* srtf_pop(SRTFQueue* queue) {
  printf("Popping a thing off the SRTFQueue\n");
}

PCB* srtf_peek(SRTFQueue* queue) {
  printf("Peeking at a thing on the SRTFQueue\n");
}


SRTFQueue createSRTFQueue() {
  SRTFQueue queue; 
  queue.head = NULL;
  queue.tail = NULL;
  queue.push = &srtf_push;
  queue.pop = &srtf_pop;
  queue.peek = &srtf_peek;

  return queue;
}
