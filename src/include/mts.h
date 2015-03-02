/*
 * Jacob Laverty
 * CS 471 Spring 2015
 * 
 *
 * MTS (Medium Term Scheduler)
 *
 * Purpose is to provide an implementation of RAM or a place for processes 
 * that have not yet arrived in the system to live. Since we want to parse
 * the input file at one time, we will create the stucture for these processes
 * and hold them in a sorted heap until they are to "arrive". Here the "MTS" will move
 * the appropriate process in to the simulation's Ready Queue where it will be properly handled.
 *
 * 
 */
#ifndef MTS_H
#define MTS_H

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "pcb.h"
#include "scheduler.h"

#define CREATE 0

int yylex();
extern char* yytext;
extern FILE* yyin;

typedef struct NodeStruct {
  PCB* pcb;
  struct NodeStruct* next;
} Node; 

Node *head;
Node *curr;

// Starts the parsing of the input file
// Builds out each process structure and places it into a heap node
// at the end of completion the heap is sorted
int mts_start(char* filelocation);

//Sorts the process based on arrival time
void print_list();

// Does MTS on tick
// This is when a process is to "arrive"
// Each tick checks the first process in the heap.
// If it is to arrive at the current tick then it is sent off as a message body
// via the mts_event_send
short mts_tick();
#endif
