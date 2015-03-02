#include "mts.h"

int mts_start(char* filelocation) {
  int n;
  head = NULL;
  curr = head;

  yyin = fopen(filelocation, "r");
  while(n=yylex()) {
    switch(n) {
      case QUANTUM:
          n = yylex();
          if(n == EOL) {
            create_queue(atoi(yytext));
          } else {
            printf("Error in parsing\n");
            return 0;
          }
        break;
      case PROCESS_ID:
        n = yylex();
        if(n == EOL) {
          //Create a new heap
          Node *node = malloc(sizeof(Node));

          //Create a new process
          node -> pcb = malloc(sizeof(PCB));
          InitPCB(&node -> pcb);

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
        n = yylex();
        if(n == EOL) {
          curr -> pcb -> arrivaltime = atoi(yytext);
        } else {
          printf("Error in parsing\n %d, %s\n", n, yytext);
          return 0;
        }
        break;
      case CPU_BURST:
        n = yylex();
        if(n == EOL) {
          Burst* burst = malloc(sizeof(Burst));
          SetBurstType(burst, 0);
          SetBurstID(burst, 0);
          SetBurstDuration(burst, atoi(yytext));
          curr->pcb->push(curr->pcb, burst);
        } else {
          printf("Error in parsing\n");
          return 0;
        }
        break;
      case IO_BURST:
        n = yylex();
        if(n == EOL){
          Burst* b = malloc(sizeof(Burst));
          SetBurstType(b, 1);
          SetBurstDuration(b, atoi(yytext));
          n = yylex();
          if(n == IO_DEVICE_ID) {
            n = yylex();
            if(n == EOL) {
              SetBurstID(b, atoi(yytext));
            } else {
              printf("Error in parsing\n");
            }
          } else {
            printf("Error in parsing\n");
            return 0;
          }
          curr->pcb->push(curr->pcb, b);
        } else {
          printf("Error in parsing\n");
          return 0;
        }
        break;
    }
  }
  curr = head;
  return 0;
}

void print_list(Node* curr) {
  while(curr!=NULL) {
    curr = curr->next;
  }
}

short mts_tick(long time) {
  if(curr == NULL) {
    return 1;
  } else if(curr != NULL && curr->pcb->arrivaltime == time) {
    process_arrival(curr->pcb, time);
    curr = curr->next;
  }
  return 0;
}
