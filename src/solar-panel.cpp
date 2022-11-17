#include "solar-panel.h"

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

uint8_t SolarPanel::output_power() const {
  return pwr_out;
}

bool SolarPanel::is_extracted() const {
  return extracted;
}
