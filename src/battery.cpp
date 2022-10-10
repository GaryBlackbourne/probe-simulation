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

void Battery::set_pwr_in(uint8_t p_in) {
  pwr_in = p_in;
}

void Battery::req_pwr_out(uint8_t p_out) {
  // todo: output range
  pwr_out = p_out;
}

void Battery::simulation_step() {
  if(enabled){
    if(charging){
      charge_level += pwr_in;
      pwr_out = 0;
    }else{
      charge_level -= pwr_out;
    }
  }
}
