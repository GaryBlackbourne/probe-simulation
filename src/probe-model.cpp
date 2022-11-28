#include "probe-model.h"
#include <pthread.h>
#include <string.h>

#include "nlohmann/json.hpp"
#include "pwr-mngr.h"

using json = nlohmann::json;

Probe::Probe() {
  simulation_run = true;
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
  pwr_manager.simulation_step();
  unlock();
  return;
}

bool Probe::is_sim_running() const {
  return simulation_run;
}

void Probe::start_simulation() {
  simulation_run = true;
}

void Probe::stop_simulation() { simulation_run = false; }

PowerManager &Probe::power_manager() { return pwr_manager; }

/*
bool Probe::add_battery(std::string &name) {
  return pwr_manager.add_battery(name);
}

bool Probe::remove_battery(std::string &name) {
  return pwr_manager.remove_battery(name);
}

bool Probe::rename_battery(std::string &old_name, std::string &new_name) {
  return pwr_manager.rename_battery(old_name, new_name);
}

bool Probe::add_solar_panel(std::string &name) {
  return pwr_manager.add_solar_panel(name);
}

bool Probe::remove_solar_panell(std::string &name) {
  return pwr_manager.remove_solar_panel(name);
}

bool Probe::rename_solar_panel(std::string &old_name, std::string &new_name) {
  return pwr_manager.rename_solar_panel(old_name, new_name);
}
*/
