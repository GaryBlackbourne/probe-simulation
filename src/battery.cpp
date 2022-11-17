#include "battery.h"
#include <cstdint>


Battery::Battery() {
  charge_level = 500000;
  charge();
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

void Battery::simulation_step(uint8_t pwr_required, uint8_t pwr_available) {}
