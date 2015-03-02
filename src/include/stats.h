#ifndef STATS_H
#define STATS_H

#include <stdlib.h>
#include <stdio.h>

int avg_wait_time;
int avg_turnaround_time; 
int wcount;
int tcount;

void submit_wait_time(int wait);
void submit_turnaround_time(int time);
void print_results(FILE* out);
void init_stats();
#endif

