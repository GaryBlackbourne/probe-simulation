#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "probe-model.h"

#define SIMULATION_RESOLUTION_US 500000 // us = 500 ms

pthread_mutex_t simulation_lock;
bool run = true;

Probe probe_model;

void simulation_loop(){

  // initialize new simulated step.
  Probe new_state = probe_model;

  uint8_t sum_power_req = 0;


  // handle motors

  
  // handle gps

  
  // handle pwr mngr
  new_state.pwr_manager = pwr_mngr_simulation_step(&probe_model.pwr_manager, sum_power_req);


  // new state overwrites old one
  probe_model = new_state;
  return;
}

int main(int argc, char* argv[]){

  pthread_mutex_init(&simulation_lock, NULL);
  
  while(run){

    pthread_mutex_lock(&simulation_lock);
    simulation_loop();
    pthread_mutex_unlock(&simulation_lock);

    usleep(SIMULATION_RESOLUTION_US);
  }
  return 0;
}
