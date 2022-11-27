#ifndef _PWR_MNGR_H
#define _PWR_MNGR_H

#include <stdint.h>
#include <stdbool.h>
#include <vector>

#include "battery.h"
#include "solar-panel.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class PowerManager{
private:

  std::vector<Battery> batteries;

  std::vector<SolarPanel> solar_panels;

  uint16_t pwr_draw;
  
  bool valid_pwr_draw;
  
  void simulation_step_consumption(uint8_t pwr_required);
  void simulation_step_production();

public:

  PowerManager();
  ~PowerManager();

  void set_pwr_draw(uint16_t);
  uint16_t get_pwr_draw() const;
  
  [[nodiscard]] uint8_t get_active_batteries_cnt() const;
  [[nodiscard]] uint8_t get_charging_batteries_cnt() const;
  [[nodiscard]] uint8_t get_enabled_batteries_cnt() const;

  bool pwr_draw_is_valid() const;

  bool add_battery(std::string& name);
  bool remove_battery(std::string& name);
  bool rename_battery(std::string& old_name, std::string new_name);

  bool add_solar_panel(std::string& name);
  bool remove_solar_panel(std::string& name);
  bool rename_solar_panel(std::string& old_name, std::string new_name);

  json serialize();
  
  //  [[nodiscard]] uint8_t get_extracted_solar_panels_cnt() const;nlohmann::
  [[nodiscard]] uint8_t get_solar_power_sum() const;
  
  void simulation_step();
};

#endif
