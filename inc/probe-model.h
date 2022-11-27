#ifndef _ROVER_MODEL_H
#define _ROVER_MODEL_H

#include <cstdint>
#define PWR_CONSUMPTION 100

#include <pthread.h>
#include <string.h>

#include "pwr-mngr.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Probe{
private:

  PowerManager pwr_manager;

  pthread_mutex_t probe_lock;

  bool simulation_run;

public:

  Probe();
  ~Probe();

  void lock();
  void unlock();

  json serialize();

  void start_simulation();
  void stop_simulation();

  bool is_sim_running() const;


  bool add_battery(std::string& name);
  bool remove_battery(std::string& name);
  bool rename_battery(std::string& old_name, std::string& new_name);

  bool add_solar_panel(std::string& name);
  bool remove_solar_panell(std::string& name);
  bool rename_solar_panel(std::string& old_name, std::string& new_name);

  void set_pwr_consumption(uint16_t pwr_draw);
  uint16_t get_pwr_draw() const;
  
  void simulate_step();
};

#endif
