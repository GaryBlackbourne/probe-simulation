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
