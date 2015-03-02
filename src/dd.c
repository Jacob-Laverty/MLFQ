#include "dd.h"

void device_list_push(DeviceList* device_list, PCB* process, int id) {
  DeviceNode* curr = device_list->head;
  while(curr != NULL && curr->device->id != id) {
    curr = curr->nextdevice;
  }
  curr->device->push(curr->device, process);
}
void device_list_insert(DeviceList* device_list, Device* device) {
  DeviceNode* n = malloc(sizeof(DeviceNode));
  n -> device = device;
  n -> nextdevice = NULL;
  if(device_list->head == NULL) {
    device_list->head = n;
  } else {
    DeviceNode* curr = device_list->head;
    while(curr->nextdevice != NULL) {
      curr = curr->nextdevice;
    }
    curr->nextdevice = n;
  }
}

void device_list_tick(DeviceList* device_list) {
  DeviceNode* curr = device_list -> head;
  while(curr != NULL) {
    curr->device->work(curr->device);
    curr = curr->nextdevice;
  }
  return;
}

void setup_devices(DeviceList* devices) {
  int i;
  for(i=1; i<=10; i++) {
    Device* d = malloc(sizeof(Device));
    InitDevice(&d, i);
    devices->insert(devices, d);
  }
}

void InitDeviceList(DeviceList** device_list) {
  (*device_list)->head = NULL;
  (*device_list)->insert = &device_list_insert;
  (*device_list)->tick = &device_list_tick;
  (*device_list)->push = &device_list_push;
}

void init_dd() {
  device_list = malloc(sizeof(DeviceList));
  InitDeviceList(&device_list);
  setup_devices(device_list);
}

void io_tick() {
  device_list->tick(device_list);
}

void move_io_to_cpu(time) {
  DeviceNode* curr = device_list -> head;
  while(curr != NULL) {
    if(curr->device->device_queue_size > 0) {
      PCB* p = curr -> device -> peek(curr->device);
      if(p->get_remaining_burst(p) == 0) {
        p->pop(p);
        if(p->peek(p) != NULL) {
          curr->device->pop(curr->device);

          sprintf(event_message_buffer, "Process %d: finished IO burst\n", p->pid, time);
          trigger_event(time);

          process_arrival(p, time);
        } else {
          curr->device->pop(curr->device);

          sprintf(event_message_buffer, "Process %d: finished IO burst\n", p->pid, time);
          trigger_event(time);

          submit_turnaround_time(time - p->arrivaltime);
          submit_wait_time(p->waittime);
        }
      }
    }
    curr = curr->nextdevice;
  }
}

void print_device_list(FILE* out) {
  DeviceNode* curr = device_list->head; 
  while(curr != NULL) {
    fprintf(out, "IO Device %d:", curr->device->id);
    if(curr->device->device_queue_size > 0) {
      curr->device->print(curr->device, out);
    } else {
      fprintf(out, " [ ]\n");
    }
    curr = curr->nextdevice;
  }
}
