#include "srtf_queue.h"

void srtf_wait(SRTFQueue* queue) {
  SRTFQueueNode* curr = queue -> head;
  while(curr != NULL) {
    if(curr->process->state == 0) {
      curr -> process -> waittime++;
    }
    curr = curr -> next;
  }
}

int get_srtf(SRTFQueue* queue) {
  return queue->head->remaining_time;
}

void srtf_push(SRTFQueue* queue, PCB* process) {
  SRTFQueueNode* n = malloc(sizeof(SRTFQueueNode));
  n -> process = process;
  n -> remaining_time = process->get_remaining_burst(process);
  n -> next = NULL;
  if(queue->head == NULL) {
    queue -> head = n;
    queue->tail = n;
  } else {
    if(queue->head->remaining_time > n->remaining_time) {
      n->next = queue->head;
      queue->head = n;
    } else {
      queue->tail->next = n;
      queue->tail = n;
    }
  }
  queue->size++;
}

PCB* srtf_pop(SRTFQueue* queue) {
  SRTFQueueNode* temp = queue->head;
  PCB* process = temp -> process;
  queue->head = temp->next;
  queue->size--;
  free(temp);
  return process;
}

PCB* srtf_peek(SRTFQueue* queue) {
  if(queue->head != NULL) {
    return queue->head->process;
  } else {
    return NULL;
  }
}


void createSRTFQueue(SRTFQueue** queue) {
  *queue = malloc(sizeof(SRTFQueue)); 
  (*queue)->head = NULL;
  (*queue)->tail = NULL;
  (*queue)->size = 0;
  (*queue)->get_srtf = &get_srtf;
  (*queue)->push = &srtf_push;
  (*queue)->pop = &srtf_pop;
  (*queue)->peek = &srtf_peek;
  (*queue)->wait = &srtf_wait;
}

void print_srtf_queue(SRTFQueue* queue, FILE* out) {
  SRTFQueueNode* itr = queue->head;
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
}
