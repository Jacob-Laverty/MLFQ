#include "timer.h"
#include "mts.h"

void timer_start() {
  time = 0;
  while(time<20){
    tick();
  }
}

void tick() {
  mts_tick(time);
  time++;
}
