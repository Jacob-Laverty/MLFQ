#include "rr_queue.h"

void rr_wait(RRQueue* queue) {
  RRQueueNode* curr = queue -> head;
  while(curr != NULL) {
    if(curr->process->state == 0) {
      curr->process->waittime++;
    }
    curr = curr->next;
  }
}

int get_quantum(RRQueue* queue) {
  return queue->head->remaining_quantum;  
}

void rr_push(RRQueue* queue, PCB* process) {
  RRQueueNode* n = malloc(sizeof(RRQueueNode));
  n -> process = process;
  n -> remaining_quantum = queue -> quantum;
  n -> next = NULL;

  if(queue -> head == NULL) {
    queue->head = n;
  } else {
    queue->tail->next = n;
  }
  queue->tail = n;
  queue->size++;

}

PCB* rr_pop(RRQueue* queue) {
  RRQueueNode* temp = queue->head;
  PCB* process = temp->process;
  queue->head = temp->next;
  queue->size--;
  free(temp);
  return process;
}

PCB* rr_peek(RRQueue* queue) {
  if(queue->head != NULL) {
    return (queue->head->process);
  } else {
    return NULL;
  }
}


void createRRQueue(RRQueue** queue, int quantum) {
  *queue = malloc(sizeof(RRQueue));
  (*queue)->head = NULL;
  (*queue)->tail = NULL;
  (*queue)->quantum = quantum;
  (*queue)->size = 0;
  (*queue)->get_quantum = &get_quantum;
  (*queue)->push = &rr_push;
  (*queue)->pop = &rr_pop;
  (*queue)->peek = &rr_peek;
  (*queue)->wait = &rr_wait;
}

void print_rr_queue(RRQueue* queue, FILE* out) {
  RRQueueNode* itr = queue->head;
  fprintf(out, "[ ");
  while(itr != NULL) {
    if(itr->process->state == 0) {
      fprintf(out, "Process %d",itr->process->pid);
      itr = itr->next;
      if(itr != NULL) {
        if(itr->process->state == 0) {
          fprintf(out, ", ");
        }
      }
    } else {
      itr = itr->next;
    }
  } 
  fprintf(out, " ]\n");
  return;
}

