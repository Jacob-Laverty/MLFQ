#include "scheduler.h"

void init_scheduler() {
  first_queue = NULL;
  second_queue = NULL;
  third_queue = NULL;
  state = malloc(sizeof(CPUState));
  state->current_process = NULL;
  state->allowed_runtime = 0;
}

void create_queue(int quantum) {
  if(first_queue == NULL) {
    createRRQueue(&first_queue, quantum);
  } else if(second_queue == NULL) {
    createRRQueue(&second_queue, quantum);
    createSRTFQueue(&third_queue);
  } 
}
void demote(long time) {
  if(state->allowed_runtime == 0 && state -> current_process != NULL){
    PCB* tmp;
    switch(state->priority) {
      case 0:
        tmp = first_queue->pop(first_queue);
        second_queue->push(second_queue, tmp);
        
        state->current_process->state = 0;
        sprintf(event_message_buffer, "Demoting PID: %d\n", state->current_process->pid);
        trigger_event(time);

        state->current_process = NULL;
        state->allowed_runtime = 0;
        state->priority = -1;
        break;
      case 1:
        tmp = second_queue->pop(second_queue);
        third_queue->push(third_queue, tmp);

        state->current_process->state = 0;
        sprintf(event_message_buffer, "Demoting PID: %d\n", state->current_process->pid);
        trigger_event(time);

        state->current_process = NULL;
        state->allowed_runtime = 0;
        state->priority = -1;
      case 2:
        break;
    }
  }
}

void move_cpu_to_io(long time) {
  if(state->current_process == NULL) {
    return;
  }
  if(state->current_process->get_remaining_burst(state->current_process) == 0) {
    state->current_process->state = 0;
    PCB* tmp = NULL;
    switch(state->priority) {
      case 0:
        tmp = first_queue->pop(first_queue);
        break;
      case 1:
        tmp = second_queue->pop(second_queue);
        break;
      case 2:
        tmp = third_queue->pop(third_queue);
        break;
    }
    tmp->pop(tmp);
    if(tmp->peek(tmp) != NULL) {
      device_list->push(device_list, tmp, tmp->peek(tmp)->id);

      sprintf(event_message_buffer, "Process %d finished burst\nProcess %d requested I/O on Device %d\n", tmp->pid, tmp->pid, tmp->peek(tmp)->id);
      trigger_event(time);

      state -> current_process = NULL;
      state -> allowed_runtime = 0;
      state -> priority = -1;
    } else {
      sprintf(event_message_buffer, "Process %d finished burst\n", tmp->pid);
      trigger_event(time);

      //No more bursts
      submit_turnaround_time(time - state->current_process->arrivaltime);
      submit_wait_time(state->current_process->waittime);
      state -> current_process = NULL;
      state -> allowed_runtime = 0;
      state -> priority = -1;
    }
  } 
}

void scheduler_tick(long time) {
  demote(time);
  if(state->current_process == NULL) {
    //CPU is currently idle
    //Assign highest priority process
    state->current_process = first_queue->peek(first_queue);
    if(state->current_process != NULL) {
      //I have a high priority process
      state->allowed_runtime = first_queue->get_quantum(first_queue);
      state->priority = 0;
      state->current_process->state = 1;

      sprintf(event_message_buffer, "Dispatched Process %d\n", state->current_process->pid);
      trigger_event(time);
      return;
    } 
    state->current_process = second_queue->peek(second_queue); 
    if(state->current_process != NULL) {
      state->allowed_runtime = second_queue->get_quantum(second_queue);
      state->priority = 1;
      state->current_process->state = 1;

      sprintf(event_message_buffer, "Dispatched Process %d\n", state->current_process->pid);
      trigger_event(time);
      return;
    }
    state->current_process = third_queue ->peek(third_queue);
    if(state->current_process != NULL) {
      //SRTF no qunatum needed
      state->allowed_runtime = 0;
      state->priority = 2;
      state->current_process->state = 1;

      sprintf(event_message_buffer, "Dispatched Process %d\n", state->current_process->pid);
      trigger_event(time);
      return;
    }
    return;
  } else {
    //CPU is currently running a process.
    //Check to see the currently running priority level and ensure there is not 
    //A higher priority process waiting in the Qs.
    switch(state->priority) {
      case 0:
        //High priority process already running allow it to continue
        break;
      case 1:
        if(first_queue->peek(first_queue) != NULL) {
          //Middle prio task is running and we have a higher prio task waiting.
          sprintf(event_message_buffer, "Process %d preempted\nProcess %d dispatched\n",
              state->current_process->pid, first_queue->peek(first_queue)->pid);
          trigger_event(time);
          state->current_process->state = 0;

          state->current_process = first_queue->peek(first_queue);
          state->allowed_runtime = first_queue->get_quantum(first_queue);
          state->priority = 0;
          state->current_process->state = 1;

        } // Else no higher priority task is running; Allow this one to continue
        break;
      case 2:
        if(first_queue->peek(first_queue) != NULL) {
          sprintf(event_message_buffer, "Process %d preempted\nProcess %d dispatched\n",
              state->current_process->pid, first_queue->peek(first_queue)->pid);
          trigger_event(time);

          //Found a higher priority process waiting.
          state->current_process->state = 0;
          state->current_process = first_queue->peek(first_queue);
          state->allowed_runtime = first_queue->get_quantum(first_queue);
          state->priority = 0;
          state->current_process->state = 1;

        } else if(second_queue->peek(second_queue) != NULL) {
          sprintf(event_message_buffer, "Process %d preempted\nProcess %d dispatched\n",
              state->current_process->pid, second_queue->peek(second_queue)->pid);
          trigger_event(time);

          //Found a higher priority process waiting.
          state->current_process->state = 0;
          state->current_process = second_queue->peek(second_queue);
          state->allowed_runtime = second_queue->get_quantum(second_queue);
          state->priority = 1;
          state->current_process->state = 1;

        } else if(third_queue->peek(third_queue) != NULL && third_queue->get_srtf(third_queue) < state->allowed_runtime) {
          sprintf(event_message_buffer, "Process %d preempted\nProcess %d dispatched\n",
              state->current_process->pid, third_queue->peek(third_queue)->pid);
          trigger_event(time);

          //Found a process with shorter time remaining;
          state->current_process->state = 0;
          state->current_process = third_queue->peek(third_queue);
          state->allowed_runtime = third_queue->get_srtf(third_queue);
          state->priority = 2;
          state->current_process->state = 1;
        }
        break;
    }
  }
  first_queue->wait(first_queue);
  second_queue->wait(second_queue);
  third_queue->wait(third_queue);
}

void process_arrival(PCB* process, long time) {
  first_queue->push(first_queue, process);
  sprintf(event_message_buffer, "Process %d arrived\n", process->pid);
  trigger_event(time);
}
