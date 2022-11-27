#include "pwr-mngr.h"
#include "battery.h"
#include "solar-panel.h"
#include <stdint.h>
#include <limits>
#include <string>

//---------------------------
//  PowerManager
//---------------------------
PowerManager::PowerManager() {
  // init battery management with two batteries
  batteries.push_back(Battery{"battery 1"});
  batteries.push_back(Battery{"battery 2"});

  // init solar farm with solar panels
  solar_panels.push_back(SolarPanel{"solar panel 1"});
  valid_pwr_draw = true;
}

PowerManager::~PowerManager() {}

uint8_t PowerManager::get_active_batteries_cnt() const {
  uint8_t battery_cnt = 0;

  for(auto& bat : batteries){
    if(bat.is_active()){
      battery_cnt ++;
    }
  }
  
  return battery_cnt;
}

uint8_t PowerManager::get_charging_batteries_cnt() const {
  uint8_t battery_cnt = 0;

  for(auto& bat: batteries){
    if(bat.is_charging()){
      battery_cnt ++;
    }
  }
  return battery_cnt;
}

uint8_t PowerManager::get_enabled_batteries_cnt() const {
  uint8_t battery_cnt = 0;

  for(auto& bat : batteries){
    if(bat.is_enabled()){
      battery_cnt ++;
    }
  }
  return battery_cnt;
}

uint8_t PowerManager::get_solar_power_sum() const {
  uint8_t pwr_out = 0;
  
  for(auto& sol : solar_panels){
    pwr_out += sol.output_power();
  }
  
  return pwr_out;
}

void PowerManager::simulation_step_consumption(uint8_t pwr_required) {
  
  uint8_t consumption = pwr_required;         // ennyit fogyasztunk
  uint8_t active_batteries_cnt = get_active_batteries_cnt();

  if((active_batteries_cnt == 0) & (pwr_required > 0)){
    valid_pwr_draw = false;
    return;
  }else{
    valid_pwr_draw = true;
  }

  uint8_t consumption_per_bat = consumption / active_batteries_cnt;

  uint8_t remaining = consumption;
  uint8_t old_remaining = 0;
  while((consumption_per_bat != 0) && (old_remaining != remaining)){
    old_remaining = remaining;
    remaining = 0;
    for(auto& bat: batteries){
      remaining += bat.discharge(consumption_per_bat);
    }
    consumption_per_bat = remaining / active_batteries_cnt;
  }

  if(remaining != 0){
    valid_pwr_draw = false;
  }
  
  return;
}

void PowerManager::simulation_step_production() {
  
  uint8_t production = get_solar_power_sum(); // ezzel töltünk
  uint8_t charging_batteries_cnt = get_charging_batteries_cnt();

  if(charging_batteries_cnt == 0){
    return;
  }
  
  uint8_t production_per_bat = production / charging_batteries_cnt;

  uint8_t remaining = production;
  uint8_t old_remaining = 0;
  while((production_per_bat != 0) && (remaining != old_remaining)){
    old_remaining = remaining;
    remaining = 0;
    for (auto& bat : batteries) {
      remaining += bat.charge(production_per_bat);
    }
    production_per_bat = remaining / charging_batteries_cnt;
  }

  return;
}

void PowerManager::simulation_step(uint8_t pwr_required) {
  simulation_step_consumption(pwr_required);
  simulation_step_production();
  return;
}

/** @TODO */
json PowerManager::serialize(){

  json pwr_manager_data_json;
  pwr_manager_data_json["valid_power_draw"] = (valid_pwr_draw) ? "true" : "false";
  
  unsigned idx = 0;
  for(auto& bat : batteries){
    pwr_manager_data_json[bat.get_name()] = bat.serialize();
    idx ++;
  }
  
  idx = 0;
  for(auto& sol : solar_panels){
    pwr_manager_data_json[sol.get_name()] = sol.serialize();
    idx++;
  }

  return pwr_manager_data_json;
}
