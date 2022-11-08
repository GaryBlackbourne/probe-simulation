#include "probe-model.h"
#include "pthread.h"

Probe::Probe() {
  pthread_mutex_init(&probe_lock, NULL);
}

Probe::~Probe() {
  pthread_mutex_destroy(&probe_lock);
}

void Probe::simulate_step() {

  pthread_mutex_lock(&probe_lock);

  pwr_manager.simulation_step(PWR_CONSUMPTION);
  
  pthread_mutex_unlock(&probe_lock);

}
