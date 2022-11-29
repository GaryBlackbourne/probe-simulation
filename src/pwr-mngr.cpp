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
  pwr_draw = 100;
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

void PowerManager::simulation_step() {
  simulation_step_consumption(pwr_draw);
  simulation_step_production();
  return;
}

bool PowerManager::add_battery(std::string &name) {
  for(auto& bat : batteries){
    if(bat.get_name() == name){
      return false;
    }
  }
  batteries.push_back(Battery{name});
  return true;
}

bool PowerManager::add_battery(Battery&& newbattery){
  for(auto& bat : batteries){
    if(bat.get_name() == newbattery.get_name()){
      return false;
    }
  }
  batteries.push_back(std::move(newbattery));
  return true;
}

bool PowerManager::remove_battery(std::string &name) {
  for(auto it = batteries.begin(); it != batteries.end(); it++){
    if (it->get_name() == name){
      batteries.erase(it);
      return true;
    }
  }
  return false;
}

bool PowerManager::rename_battery(std::string &old_name, std::string new_name) {
  Battery* target = nullptr;

  for(auto& bat : batteries) {
    if(bat.get_name() == new_name){
      return false;
    }
    if(bat.get_name() == old_name){
      target = &bat;
    }
  }

  if(target != nullptr){
    target->set_name(std::move(new_name));
    return true;
  }
  return false;
}

bool PowerManager::add_solar_panel(std::string &name) {
  for(auto& sol : solar_panels){
    if(sol.get_name() == name){
      return false;
    }
  }
  solar_panels.push_back(SolarPanel{name});
  return true;
}

bool PowerManager::add_solar_panel(SolarPanel &&newsolarpanel) {
  for(auto& sol : solar_panels){
    if(sol.get_name() == newsolarpanel.get_name()){
      return false;
    }
  }
  solar_panels.push_back(std::move(newsolarpanel));
  return true;
}

bool PowerManager::set_battery_charging(std::string &name, bool charging_param) {
  bool exist = false;
  for(auto& bat : batteries) {
    if(bat.get_name() == name){
      exist = true;
      if(charging_param) {
	bat.charge();
      } else {
	bat.stop_charge();
      }
    }
  }
  return exist;
}

bool PowerManager::enable_battery(std::string &name) {
  bool exist = false;
  for (auto& bat : batteries) {
    if(bat.get_name() == name){
      exist = true;
      bat.enable();
    }
  }
  return exist;
}

bool PowerManager::disable_battery(std::string &name) {
  bool exist = false;
  for(auto& bat : batteries){
    if(bat.get_name() == name){
      exist = true;
      bat.disable();
    }
  }
  return exist;
}



bool PowerManager::remove_solar_panel(std::string &name) {
  for(auto it = solar_panels.begin(); it != solar_panels.end(); it++){
    if(it->get_name() == name){
      solar_panels.push_back(SolarPanel{name});
      return true;
    }
  }
  return false;
}

bool PowerManager::rename_solar_panel(std::string &old_name, std::string new_name) {
  SolarPanel* target = nullptr;

  for(auto& sol : solar_panels) {
    if(sol.get_name() == new_name){
      return false;
    }
    if(sol.get_name() == old_name){
      target = &sol;
    }
  }

  if(target != nullptr){
    target->set_name(std::move(new_name));
    return true;
  }
  return false;
}

bool PowerManager::extract_solar_panel(std::string &name, uint8_t level) {
  bool exist = false;
  for (auto& sol : solar_panels){
    if(sol.get_name() == name){
      exist = true;
      sol.set_extract_level(level);
    }
  }
  return exist;
}

json PowerManager::batteries_serialize() const {
  json batteries_json;
  unsigned idx = 0;
  for(auto& bat : batteries){
    batteries_json[bat.get_name()] = bat.serialize();
    idx ++;
  }
  return batteries_json;
}

json PowerManager::solar_panels_serialize() const {
  json solar_panels_json;
  unsigned idx = 0;
  for(auto& sol : solar_panels){
    solar_panels_json[sol.get_name()] = sol.serialize();
    idx++;
  }
  return solar_panels_json;
}

json PowerManager::serialize(){

  json pwr_manager_data_json;
  pwr_manager_data_json["valid_power_draw"] = (valid_pwr_draw) ? "true" : "false";
  pwr_manager_data_json["pwr_draw"] = this->pwr_draw;

  pwr_manager_data_json["batteries"] = batteries_serialize();
  pwr_manager_data_json["solar-panels"] = solar_panels_serialize();

  return pwr_manager_data_json;
}

void PowerManager::set_pwr_draw(uint16_t pwr_draw) {
  // maybe set maximal pwr draw?
  this->pwr_draw = pwr_draw;
  return;
}

uint16_t PowerManager::get_pwr_draw() const {
  return this->pwr_draw;
}
