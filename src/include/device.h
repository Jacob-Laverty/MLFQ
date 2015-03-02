#ifndef DEVICE_H
#define DEVICE_H

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"


typedef struct DeviceQueueNodeStruct {
  PCB* process;
  struct DeviceQueueNodeStruct* nextprocess;
} DeviceQueueNode;

typedef struct DeviceStruct {
  DeviceQueueNode* head;
  DeviceQueueNode* tail;
  int device_queue_size;
  int id;

  void (*work) (struct DeviceStruct*);
  void (*push) (struct DeviceStruct*, PCB*);
  PCB* (*pop) (struct DeviceStruct*);
  PCB* (*peek) (struct DeviceStruct*);
  void (*print) (struct DeviceStruct*, FILE*);
} Device;

void print(Device* device, FILE* out);
void work(Device* device);
void device_queue_push(Device* device, PCB* process);
PCB* device_queue_pop(Device* device);
PCB* device_queue_peek(Device* device);

void InitDevice(Device** device, int id);

#endif
