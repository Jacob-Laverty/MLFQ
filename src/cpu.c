#include "cpu.h"

int cpu_tick(time) {
  if(state -> current_process != NULL) {
    state->current_process->headburst->burst->duration--;
    state->allowed_runtime--;
  } else {
    return 0;
  }
}
