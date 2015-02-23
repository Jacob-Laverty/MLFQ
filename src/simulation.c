#include "simulation.h"
#include "timer.h"

int main(int argc, char **argv) {
  printf("Hello world\n");

  filelocation = NULL;

  opterr = 0;

  int c;
  while((c = getopt(argc, argv, "f:")) != -1) {
    switch(c) {
      case 'f':
          filelocation = optarg;
    }
  }

  mts_start(filelocation);
  timer_start();
  return 0;
}
