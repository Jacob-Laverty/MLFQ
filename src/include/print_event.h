#ifndef PRINT_EVENT_H
#define PRINT_EVENT_H

#include "scheduler.h"
#include "dd.h"

FILE* out;
char* event_message_buffer;
void init_event_buffer();
void start_event(long time);
void event();

void trigger_event();
void print_ready_queues();
#endif
