#include "scheduler.h"

void createQueue(int quantum) {
  first_queue = createRRQueue(1);
  second_queue = createRRQueue(2);
  third_queue = createSRTFQueue();
}

void testQueues() {
  first_queue.pop(&first_queue);

  second_queue.pop(&second_queue);

  third_queue.pop(&third_queue);
}
