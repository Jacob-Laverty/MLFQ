#include "mts.h"

int mts_start(char* filelocation) {
  int n;
  head = NULL;
  curr = head;

  yyin = fopen(filelocation, "r");
  while(n=yylex()) {
    switch(n) {
      case QUANTUM:
        printf("Received a time quantum\n");
          n = yylex();
          if(n == EOL) {
            printf("Time Quantum: %s\n", yytext);
          } else {
            printf("Error in parsing\n");
            return 0;
          }
        break;
      case PROCESS_ID:
        printf("Received a new process ID\n");
        n = yylex();
        if(n == EOL) {
          //Create a new heap
          Node *node = malloc(sizeof(Node));

          //Create a new process
          node -> pcb = malloc(sizeof(PCB));
          InitPCB(node -> pcb);

          if(head == NULL) {
            head = node;
            curr = head;
          } else {
            curr -> next = node;
            curr = node;
          }

          curr -> pcb -> pid = atoi(yytext);

        } else {
          printf("Error in parsing\n"); 
          return 0;
        }
        break;
      case ARRIVAL_TIME:
        printf("Reveived the arrival time\n");
        n = yylex();
        if(n == EOL) {
          printf("Arrival time: %s\n", yytext);

          curr -> pcb -> arrivaltime = atoi(yytext);
        } else {
          printf("Error in parsing\n %d, %s\n", n, yytext);
          return 0;
        }
        break;
      case CPU_BURST:
        printf("Received a CPU Burst\n");
        n = yylex();
        if(n == EOL) {
          if(curr->pcb->headburst != NULL) {
            BurstNode* b = malloc(sizeof(BurstNode));
            b->nextburst = NULL; 
          }
          SetBurstType(curr->pcb->iterator, 0);
          SetBurstID(curr->pcb->iterator, 0);
          SetBurstDuration(curr->pcb->iterator, atoi(yytext));
          

        } else {
          printf("Error in parsing\n");
          return 0;
        }
        break;
      case IO_BURST:
        printf("Received an IO Burst\n");
        n = yylex();
        if(n == EOL){
          printf("IO Burst duration: %s\n", yytext);
        } else {
          printf("Error in parsing\n");
          return 0;
        }
        break;
      case IO_DEVICE_ID:
        printf("Received an IO Device ID\n");
        n = yylex();
        if(n == EOL) {
          printf("IO Device ID: %s\n", yytext);
        } else {
          printf("Error in parsing\n");
          return 0;
        }
        break;
    }
  }
  print_list(head);
  return 0;
}

void print_list(Node* curr) {
  while(curr!=NULL) {
    printf("New Node**\n");
    printf("Node id: %d\n", curr->pcb->pid);
    curr = curr->next;
  }
}

void mts_tick(long time) {
  if(curr->pcb->arrivaltime == time) {
    printf("Process has arrived\n");
  }
}

void mts_event(int event, Node* process) {}
