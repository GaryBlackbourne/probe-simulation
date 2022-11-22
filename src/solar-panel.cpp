#include "solar-panel.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <stdint.h>
#include <string>

SolarPanel::SolarPanel() {
  set_extract_level(0);
}

SolarPanel::~SolarPanel() {}

void SolarPanel::set_extract_level(uint8_t percentage) {

  if(percentage > 100){
    extract_level = 100;
  }else{  
    extract_level = percentage;
  }

  pwr_out = MAX_PWR_OUT * (percentage / 100);
}

json SolarPanel::serialize(){

  json solar_panel_data_json;
  solar_panel_data_json["pwr-output"] = std::to_string(pwr_out);
  solar_panel_data_json["extract-level"] = std::to_string(extract_level);
  
  return solar_panel_data_json;
}

uint8_t SolarPanel::output_power() const {
  return pwr_out;
}

uint8_t SolarPanel::get_extract_level() const {
  return extract_level;
}
