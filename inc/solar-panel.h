#ifndef _SOLAR_PANEL_H
#define _SOLAR_PANEL_H

#include "stdint.h"
#include "nlohmann/json.hpp"

#define MAX_PWR_OUT 100

using json = nlohmann::json;

class SolarPanel{
private:

  uint8_t pwr_out;

  bool extracted;

public:

  SolarPanel();
  ~SolarPanel();

  void extract();
  void retract();

  json serialize();

  [[nodiscard]] bool is_extracted() const;

  [[nodiscard]] uint8_t output_power() const;
};

#endif
