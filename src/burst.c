#include "burst.h"

void InitBurst(BurstNode* iterator) {
  if(iterator->burst == NULL) {
    iterator->burst = malloc(sizeof(Burst));
  }
}

void SetBurstType(BurstNode* iterator, int type) {
  iterator->burst->type = type;
/*
  if(iterator->burst == NULL) {
    InitBurst(iterator);
  } 
*/
}

void SetBurstID(BurstNode* iterator, int id) {
  if(iterator->burst == NULL) {
    InitBurst(iterator);
  }
  iterator->burst->id = id;
}

void SetBurstDuration(BurstNode* iterator, int duration) {
  if(iterator -> burst == NULL) {
    InitBurst(iterator);
  }
  iterator->burst->duration = duration;
}
