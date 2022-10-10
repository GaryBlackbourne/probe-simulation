#include "probe-model.h"

Probe::Probe() {
  pthread_mutex_init(&(this->probe_lock), NULL);
}

Probe::~Probe() {
  pthread_mutex_destroy(&(this->probe_lock));
}

void Probe::simulate_step() {

  return;
}