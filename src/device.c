#include "device.h"

void work(Device* device) {
  PCB* p = device->peek(device);
  if(p != NULL) {
    p->headburst->burst->duration--;
  }
}

void device_queue_push(Device* device, PCB* process) {
  DeviceQueueNode* d = malloc(sizeof(DeviceQueueNode));
  d -> process = process;
  d -> nextprocess = NULL;
  if(device->head == NULL) {
    device -> head = d; 
  } else {
    device -> tail -> nextprocess = d;
  }
  device -> device_queue_size++;
  device -> tail = d;
}

PCB* device_queue_pop(Device* device) {
  DeviceQueueNode* temp = device->head;
  PCB* p = temp->process;
  device->head = temp->nextprocess;

  device->device_queue_size--;
  free(temp);
  return p;
}

PCB* device_queue_peek(Device* device) {
  if(device->head != NULL) {
    return device->head->process;
  }
  return NULL;
}

void print(Device* device, FILE* out) {
  DeviceQueueNode* itr = device->head;
  fprintf(out, "[ ");
  while(itr != NULL) {
    fprintf(out, "Process %d", itr->process->pid);
    if(itr->nextprocess != NULL) {
      fprintf(out, ", ");
    }
    itr = itr->nextprocess;
  }
  fprintf(out, " ]\n");
}

void InitDevice(Device** device, int id) {
  (*device)->print = &print;
  (*device)->work = &work;
  (*device)->push = &device_queue_push;
  (*device)->pop = &device_queue_pop;
  (*device)->peek = &device_queue_peek;
  (*device)->head = NULL;
  (*device)->tail = NULL;
  (*device)->device_queue_size = 0;
  (*device)->id = id;
}
