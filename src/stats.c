#include "stats.h"

void init_stats() {
  avg_wait_time = 0;
  avg_turnaround_time = 0;
  wcount = 0;
  tcount = 0;
}
void submit_wait_time(int time) {
  avg_wait_time += time;
  wcount++;
}

void submit_turnaround_time(int time) {
  avg_turnaround_time+=time;
  tcount++;
}

void print_results(FILE* out) {
  fprintf(out, "Average Wait Time %d\n", (avg_wait_time/wcount));
  fprintf(out, "Average Turnaround Time %d\n", (avg_turnaround_time/tcount));
  fflush(out);
}
