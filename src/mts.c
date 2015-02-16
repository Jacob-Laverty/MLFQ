#include "mts.h"

struct Node {
  //PCB* pcb;
  node *left;
  node *right;
};


int mts_start() {
  printf("Hello from the MTS\n");

  int n;
  while(n=yylex()) {
    printf("%d %s\n", n, yytext);
  }

  return 0;
}

void heap_sort() {}

void mts_tick() {}

void mts_event(int even, node* process) {}


