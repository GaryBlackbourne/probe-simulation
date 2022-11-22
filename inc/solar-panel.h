#ifndef _SOLAR_PANEL_H
#define _SOLAR_PANEL_H

#include "stdint.h"
#include "nlohmann/json.hpp"

#define MAX_PWR_OUT 100

using json = nlohmann::json;

class SolarPanel{
private:

  uint8_t pwr_out;

  uint8_t extract_level;

public:

  SolarPanel();
  ~SolarPanel();

  void set_extract_level(uint8_t percentage);
  uint8_t get_extract_level() const;

  json serialize();

  [[nodiscard]] bool is_extracted() const;

  [[nodiscard]] uint8_t output_power() const;
};

#endif
