#include "burst.h"

void SetBurstType(Burst* b, int type) {
  b->type = type;
}

void SetBurstID(Burst* b, int id) {
  b->id = id;
}

void SetBurstDuration(Burst* b, int duration) {
  b->duration = duration;
}
