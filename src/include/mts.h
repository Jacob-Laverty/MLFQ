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

#include <stdio.h>
#include "tokens.h"

#define CREATE 0

int yylex();
extern char* yytext;

typedef struct Node node;

// Starts the parsing of the input file
// Builds out each process structure and places it into a heap node
// at the end of completion the heap is sorted
int mts_start();

//Sorts the process based on arrival time
void heap_sort();

// Does MTS on tick
// This is when a process is to "arrive"
// Each tick checks the first process in the heap.
// If it is to arrive at the current tick then it is sent off as a message body
// via the mts_event_send
void mts_tick();

// Handles MTS events
// Pushes a process into the ready Q when it "arrives"
void mts_event(int event, node *process);

