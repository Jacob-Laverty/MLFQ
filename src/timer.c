#include "timer.h"
#include "mts.h"
#include "scheduler.h"
#include "cpu.h"
#include "dd.h"

void timer_start() {
  time = 0;
  kill = 0;
  while(!kill || time<2000){
    tick();
  }
}

void tick() {
  kill = mts_tick(time);
  move_cpu_to_io(time);
  move_io_to_cpu(time);
  scheduler_tick(time);
  io_tick();
  cpu_tick(time);
  time++;
}
