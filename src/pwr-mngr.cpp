#include "pwr-mngr.h"
#include "battery.h"
#include "solar-panel.h"
#include <cstdint>

//---------------------------
//  PowerManager
//---------------------------
PowerManager::PowerManager() {
  // init battery management with two batteries
  batteries.push_back(Battery{});
  batteries.push_back(Battery{});

  // init solar farm with solar panels
  solar_panels.push_back(SolarPanel{});
}

PowerManager::~PowerManager() {}

uint8_t PowerManager::get_active_batteries_cnt() const {
  uint8_t battery_cnt = 0;

  for(auto bat : batteries){
    if(bat.is_active()){
      battery_cnt ++;
    }
  }
  
  return battery_cnt;
}

uint8_t PowerManager::get_charging_batteries_cnt() const {
  uint8_t battery_cnt = 0;

  for(auto bat: batteries){
    if(bat.is_charging()){
      battery_cnt ++;
    }
  }
  return battery_cnt;
}

uint8_t PowerManager::get_enabled_batteries_cnt() const {
  uint8_t battery_cnt = 0;

  for(auto bat : batteries){
    if(bat.is_enabled()){
      battery_cnt ++;
    }
  }
  return battery_cnt;
}

uint8_t PowerManager::get_solar_power_sum() const {
  uint8_t pwr_out = 0;
  
  for(auto sol : solar_panels){
    pwr_out += sol.output_power();
  }
  
  return pwr_out;
}

void PowerManager::simulation_step(uint8_t pwr_required) {

  uint8_t consumption = pwr_required;         // ennyit fogyasztunk
  uint8_t production = get_solar_power_sum(); // ezzel töltünk

  uint8_t consumption_per_bat = consumption / get_active_batteries_cnt();
  uint8_t production_per_bat = production / get_charging_batteries_cnt();

  uint8_t remaining = production;
  uint8_t old_remaining = 0;
  while((production_per_bat != 0) || (remaining != old_remaining)){
    old_remaining = remaining;
    remaining = 0;
    for(auto bat: batteries){
      remaining += bat.charge(production_per_bat);
    }
    production_per_bat = remaining / get_charging_batteries_cnt();
  }


  remaining = consumption;
  old_remaining = 0;
  while((consumption_per_bat != 0) || (old_remaining != remaining)){
    old_remaining = remaining;
    remaining = 0;
    for(auto bat: batteries){
      remaining += bat.discharge(consumption_per_bat);
    }
    consumption_per_bat = remaining / get_active_batteries_cnt();
  }
  
  return;
}
