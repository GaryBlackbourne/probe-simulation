#ifndef _SOLAR_PANEL_H
#define _SOLAR_PANEL_H

#include <stdint.h>
#include <string>

#include "nlohmann/json.hpp"

#define MAX_PWR_OUT 100

using json = nlohmann::json;

class SolarPanel{
private:

  uint32_t pwr_out;

  uint8_t extract_level;

  std::string name;

public:

  SolarPanel(std::string& name);
  SolarPanel(std::string&& name);
  SolarPanel(std::string& name, uint8_t extract_level);
  ~SolarPanel();

  void set_extract_level(uint8_t percentage);
  uint8_t get_extract_level() const;

  std::string get_name () const;
  void set_name(std::string&& new_name);
  
  json serialize() const;

  [[nodiscard]] bool is_extracted() const;

  [[nodiscard]] uint32_t output_power() const;
};

#endif
