#ifndef DD_H
#define DD_H

#include "device.h"
#include "scheduler.h"

typedef struct DeviceListNode {
  Device* device;
  struct DeviceListNode* nextdevice;
} DeviceNode;

typedef struct DeviceListStruct {
  DeviceNode* head;

  void (*insert) (struct DeviceListStruct*, Device*);
  void (*tick) (struct DeviceListStruct*);

  void (*push) (struct DeviceListStruct*, PCB*, int);
} DeviceList;

DeviceList* device_list;
void device_list_push(DeviceList* device_list, PCB* process, int id);
void device_list_insert(DeviceList* device_list, Device* device);
void device_list_tick(DeviceList* device_list);
void setup_devices(DeviceList* devices);
void InitDeviceList(DeviceList** device_list);
void io_tick();
void move_io_to_cpu();
void init_dd();

void print_device_list(FILE* out);
#endif
