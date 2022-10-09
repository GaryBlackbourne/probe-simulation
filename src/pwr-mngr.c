
#include "pwr-mngr.h"

PowerManager pwr_mngr_simulation_step(PowerManager* old_state, uint8_t power_req){

  // init new state of the power management module
  PowerManager new_state = *old_state;

  // set new power output
  new_state.battery1.pwr_out = power_req / 2;
  new_state.battery2.pwr_out = power_req / 2;
  
  // set new power input
  if(old_state->solar_panel.extracted){
    new_state.battery1.pwr_in = old_state->solar_panel.pwr_out / 2;
    new_state.battery2.pwr_in = old_state->solar_panel.pwr_out / 2;
  }
 
  // set new charge levels
  if(old_state->battery1.charging && old_state->battery1.charge_level < 1000000){
    new_state.battery1.charge_level += old_state->battery1.pwr_in - old_state->battery1.pwr_out;
  }
  if(old_state->battery2.charging && old_state->battery2.charge_level < 1000000){
    new_state.battery2.charge_level += old_state->battery2.pwr_in - old_state->battery2.pwr_out;
  }
    
  return new_state;
}
