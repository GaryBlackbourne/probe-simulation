#include "solar-panel.h"
#include "nlohmann/json.hpp"
#include <stdint.h>
#include <string>

SolarPanel::SolarPanel(std::string& name) {
  this->name = name;
  set_extract_level(0);
}

SolarPanel::SolarPanel(std::string&& name) {
  this->name = std::move(name);
  set_extract_level(0);
}

SolarPanel::SolarPanel(std::string& name, uint8_t extract_level){
  this->name = name;
  set_extract_level(extract_level);
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

std::string SolarPanel::get_name() const { return std::string{name}; }

void SolarPanel::set_name(std::string &&new_name){
  this->name = std::move(new_name);
}

json SolarPanel::serialize() const {

  json solar_panel_data_json;
  solar_panel_data_json["name"] = name;
  solar_panel_data_json["pwr-output"] = pwr_out;
  solar_panel_data_json["extract-level"] = extract_level;
  
  return solar_panel_data_json;
}

uint32_t SolarPanel::output_power() const {
  return pwr_out;
}

uint8_t SolarPanel::get_extract_level() const {
  return extract_level;
}

