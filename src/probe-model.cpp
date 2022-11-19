#include "probe-model.h"
#include <pthread.h>
#include <string.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

Probe::Probe() {
  pthread_mutex_init(&probe_lock, NULL);
}

Probe::~Probe() { pthread_mutex_destroy(&probe_lock); }

void Probe::lock() { pthread_mutex_lock(&probe_lock); }

void Probe::unlock() { pthread_mutex_unlock(&probe_lock); }

json Probe::serialize() {

  lock();

  json probe_data_json;
  probe_data_json["pwr-manager"] = pwr_manager.serialize();
  
  unlock();

  return probe_data_json;
}

void Probe::simulate_step() {
  lock();
  pwr_manager.simulation_step(PWR_CONSUMPTION);
  unlock();
  return;
}

