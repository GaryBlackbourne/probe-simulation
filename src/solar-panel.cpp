#include "solar-panel.h"

SolarPanel::SolarPanel() {}
SolarPanel::~SolarPanel() {}

void SolarPanel::extract_solar_panel() {
  extracted = true;

  pwr_out = MAX_PWR_OUT;
}

void SolarPanel::retract_solar_panel() {
  extracted = false;

  pwr_out = 0;
}

uint8_t SolarPanel::get_power() const {
  return pwr_out;
}

bool SolarPanel::is_extracted() const {
  return extracted;
}