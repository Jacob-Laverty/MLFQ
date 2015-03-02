#ifndef BURST_H
#define BURST_H
#include <stdlib.h>

typedef struct BurstStruct {
  int type;
  int id;
  int duration;
} Burst;

typedef struct BurstNodeStruct {
  Burst *burst;
  struct BurstNodeStruct *nextburst;

} BurstNode;

void SetBurstType(Burst* b, int type);
void SetBurstID(Burst* b, int id);
void SetBurstDuration(Burst* b, int duration);
#endif
