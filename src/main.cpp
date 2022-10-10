#include <unistd.h>

#include "probe-model.h"

#define SIMULATION_RESOLUTION_US 500000 // us = 500 ms

int main(int argc, char* argv[]){

  bool run = true;

  Probe probe_model;

  // launch comm- thread

  while(run){

    probe_model.simulate_step();

    usleep(SIMULATION_RESOLUTION_US);
  }
  return 0;
}
