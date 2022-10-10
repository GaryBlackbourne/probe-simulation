#include "battery.h"


Battery::Battery() {}
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

void Battery::simulation_step(uint8_t pwr_required, uint8_t pwr_available) {
  if(enabled){
    if(charging){ // todo: implement range
      charge_level += pwr_available;
    }else{
      charge_level -= pwr_required;
    }
  }
}
