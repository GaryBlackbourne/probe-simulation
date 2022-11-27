#ifndef _SOLAR_PANEL_H
#define _SOLAR_PANEL_H

#include <stdint.h>
#include <string>

#include "nlohmann/json.hpp"

#define MAX_PWR_OUT 100

using json = nlohmann::json;

class SolarPanel{
private:

  uint8_t pwr_out;

  uint8_t extract_level;

  std::string name;

public:

  SolarPanel(std::string name);
  SolarPanel(std::string&& name);
  ~SolarPanel();

  void set_extract_level(uint8_t percentage);
  uint8_t get_extract_level() const;

  std::string get_name () const;
  void set_name(std::string&& new_name);
  
  json serialize();

  [[nodiscard]] bool is_extracted() const;

  [[nodiscard]] uint8_t output_power() const;
};

#endif
