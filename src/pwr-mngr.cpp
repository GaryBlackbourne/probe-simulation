#include "pwr-mngr.h"

//---------------------------
//  PowerManager
//---------------------------
PowerManager::PowerManager() {}
PowerManager::~PowerManager() {}

uint8_t PowerManager::get_active_batteries_cnt() const {
  uint8_t battery_cnt = 0;
  if(battery1.is_enabled() && !battery1.is_charging()){
    battery_cnt ++;
  }
  if(battery2.is_enabled() && !battery2.is_charging()){
    battery_cnt++;
  }
  return battery_cnt;
}

uint8_t PowerManager::get_charging_batteries_cnt() const {
  uint8_t battery_cnt = 0;
  if(battery1.is_charging()){
    battery_cnt ++;
  }
  if(battery2.is_charging()){
    battery_cnt++;
  }
  return battery_cnt;
}

uint8_t PowerManager::get_online_batteries_cnt() const {
  return get_active_batteries_cnt() + get_charging_batteries_cnt();
}

void PowerManager::simulation_step(uint8_t pwr_required) {
  int active_battery_cnt = get_active_batteries_cnt();
  int charging_batteries_cnt = get_charging_batteries_cnt();
  int online_batteries_cnt = get_online_batteries_cnt();

  int solar_power = solar_panel.get_power();

  if (online_batteries_cnt && solar_panel.is_extracted()) {
    battery1.simulation_step(pwr_required / active_battery_cnt, solar_power / charging_batteries_cnt);
    battery2.simulation_step(pwr_required / active_battery_cnt, solar_power / charging_batteries_cnt);
  }
}
