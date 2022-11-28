#include "battery.h"
#include <cstdint>
#include <string>


Battery::Battery(std::string&& name) {
  charge_level = 500000;
  stop_charge();
  enable();
  this->name = std::move(name);
}

Battery::Battery(std::string& name) {
  charge_level = 500000;
  stop_charge();
  enable();
  this->name = name;
}

Battery::Battery(uint32_t charge_level, std::string& name){
  this->charge_level = charge_level;
  if(this->charge_level > 1000000){
    this->charge_level = 1000000;
  }
  this->name = name;
  stop_charge();
  enable();
}

Battery::~Battery() {}

void Battery::enable() {
  enabled = true;
}

void Battery::disable() {
  enabled = false;
}

bool Battery::is_enabled() const{
  return enabled;
}

void Battery::charge() {
  charging = true;
}

void Battery::stop_charge() {
  charging = false;
}

bool Battery::is_charging() const {
  return charging;
}

bool Battery::is_active() const { return (enabled & !charging); }

uint8_t Battery::charge(uint8_t pwr_in){

  if(!(charging && enabled)){
    return pwr_in;
  }

  if(pwr_in + charge_level > BATTERY_MAX_CHARGE_LEVEL){
    uint8_t retval = (pwr_in + charge_level) - BATTERY_MAX_CHARGE_LEVEL;
    charge_level = BATTERY_MAX_CHARGE_LEVEL;
    disable();
    return retval;
  }else{
    charge_level += pwr_in;
    return 0;
  }
}

uint8_t Battery::discharge(uint8_t pwr_out){

  if(!(!charging && enabled)){
    return pwr_out;
  }

  if(charge_level < pwr_out){
    uint8_t retval = pwr_out - charge_level;
    charge_level = 0;
    disable();
    return retval;
  }

  charge_level -= pwr_out;
  return 0;
}

void Battery::set_name(std::string &&new_name) { name = std::move(new_name); }

std::string Battery::get_name() const {
  return std::string{name};
}

json Battery::serialize() {

  json battery_data_json;
  battery_data_json["name"] = name;
  battery_data_json["charge-level"] = std::to_string(charge_level);
  battery_data_json["charging"] = (charging) ? "true" : "false";
  battery_data_json["enabled"] = (enabled) ? "true" : "false";
  
  return battery_data_json;
}
