#include "mts.h"

struct Node {
  //PCB* pcb;
  node *left;
  node *right;
};


int mts_start(char* filelocation) {
  printf("Hello from the MTS\n");

  int n;

  yyin = fopen(filelocation, "r");
  while(n=yylex()) {
    switch(n) {
      case QUANTUM:
        printf("Received a time quantum\n");
    }
  }

  return 0;
}

void heap_sort() {}

void mts_tick() {}

void mts_event(int even, node* process) {}


