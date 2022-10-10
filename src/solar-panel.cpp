#include "solar-panel.h"

SolarPanel::SolarPanel() {}
SolarPanel::~SolarPanel() {}

void SolarPanel::extract_solar_panel() {
  extracted = true;
}

void SolarPanel::retract_solar_panel() {
  extracted = false;
}
