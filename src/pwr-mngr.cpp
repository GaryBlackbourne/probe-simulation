#include "pwr-mngr.h"

//---------------------------
//  PowerManager
//---------------------------
PowerManager::PowerManager() {}
PowerManager::~PowerManager() {}

/*
PowerManager pwr_mngr_simulation_step(PowerManager* old_state, uint8_t power_req){

  // init new state of the power management module
  PowerManager new_state = *old_state;

  // set new power output (bool is an integer, we count the working batteries)
  uint8_t battery_cnt = 0;
  if(old_state->battery1.enabled) { battery_cnt ++; }
  if(old_state->battery2.enabled) { battery_cnt ++; }

  if(old_state->battery1.enabled){

    // calculate battery pwr out
    new_state.battery1.pwr_out = power_req / battery_cnt; 

    // calculate battery pwr in
    if(old_state->solar_panel.extracted){ 
      new_state.battery1.pwr_in = old_state->solar_panel.pwr_out / battery_cnt;
    }else{
      new_state.battery1.pwr_in = 0;
    }

    // calculate charge levels
    if(old_state->battery1.charging && old_state->battery1.charge_level < 1000000){
      new_state.battery1.charge_level += old_state->battery1.pwr_in - old_state->battery1.pwr_out;
    }
   
  }else{
    new_state.battery1.pwr_out = 0;
    new_state.battery1.pwr_in = 0;
  }
    
  if(old_state->battery2.enabled){
    new_state.battery2.pwr_out = power_req / battery_cnt;
  }else{
    new_state.battery2.pwr_out = 0;
  }
  
  // set new power input
  if(old_state->solar_panel.extracted){
    if(old_state->battery1.enabled){
       new_state.battery1.pwr_in = old_state->solar_panel.pwr_out / battery_cnt;
    }
    if(old_state->battery2.enabled){
      new_state.battery2.pwr_in = old_state->solar_panel.pwr_out / battery_cnt;
    }
  }else{
    new_state.battery1.pwr_in = 0;
    new_state.battery2.pwr_in = 0;
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
*/