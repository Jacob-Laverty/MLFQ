#include "print_event.h"

void init_event_buffer(){
  event_message_buffer = malloc(sizeof(char) * 1024);
}

void start_event(long time) {
  fprintf(out, "Time: %d\n", time);
}

void event() {
  fprintf(out, event_message_buffer);
}

void print_ready_queues() {
  fprintf(out, "Ready Queue 1: ");
  print_rr_queue(first_queue, out); 
  fprintf(out, "Ready Queue 2: ");
  print_rr_queue(second_queue, out); 
  fprintf(out, "Ready Queue 3: ");
  print_srtf_queue(third_queue, out);
}

void print_io_queues() {
  print_device_list(out);
}

void trigger_event(time) {
  start_event(time);
  event();
  print_ready_queues();
  print_io_queues();
  fprintf(out, "\n***************\n");
  fflush(out);
  sprintf(event_message_buffer, "");
}
