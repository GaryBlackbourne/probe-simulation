#include "solar-panel.h"
#include "nlohmann/json.hpp"
#include <stdint.h>
#include <string>

SolarPanel::SolarPanel() {
  this->extract();
}
SolarPanel::~SolarPanel() {}

void SolarPanel::extract() {
  extracted = true;

  pwr_out = MAX_PWR_OUT;
}

void SolarPanel::retract() {
  extracted = false;

  pwr_out = 0;
}

json SolarPanel::serialize(){

  json solar_panel_data_json;
  solar_panel_data_json["pwr-output"] = std::to_string(pwr_out);
  solar_panel_data_json["extracted"] = (extracted) ? "true" : "false";
  
  return solar_panel_data_json;
}

uint8_t SolarPanel::output_power() const {
  return pwr_out;
}

bool SolarPanel::is_extracted() const {
  return extracted;
}
