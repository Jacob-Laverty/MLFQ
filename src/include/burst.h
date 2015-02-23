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

void InitBurst(BurstNode* iterator);
void SetBurstType(BurstNode* iterator, int type);
void SetBurstID(BurstNode* iterator, int id);
void SetBurstDuration(BurstNode* iterator, int duration);
#endif
