#include "simulation.h"

int main(int argc, char **argv) {
  filelocation = NULL;
  outlocation = NULL;

  opterr = 0;

  int c;
  while((c = getopt(argc, argv, "f:o:")) != -1) {
    switch(c) {
      case 'f':
        filelocation = optarg;
        break;
      case 'o':
        outlocation = optarg; 
        out = fopen(outlocation, "w");
        break;
    }
  }

  init_stats();
  init_event_buffer();
  init_scheduler();  
  init_dd();
  mts_start(filelocation);
  timer_start();
  print_results(out);
  fclose(out);
  return 0;
}
