#ifndef _PWR_MNGR_H
#define _PWR_MNGR_H

#include <cstdint>
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

  uint32_t pwr_draw;
  
  bool valid_pwr_draw;
  
  void simulation_step_consumption(uint32_t pwr_required);
  void simulation_step_production();

  json batteries_serialize() const;
  json solar_panels_serialize() const;

public:

  PowerManager();
  ~PowerManager();

  [[nodiscard]] uint8_t get_active_batteries_cnt() const;
  [[nodiscard]] uint8_t get_charging_batteries_cnt() const;
  [[nodiscard]] uint8_t get_enabled_batteries_cnt() const;

  void set_pwr_draw(uint32_t);
  uint32_t get_pwr_draw() const;
  bool pwr_draw_is_valid() const;

  bool add_battery(std::string& name);
  bool add_battery(Battery&& newbattery);
  bool remove_battery(std::string& name);
  bool rename_battery(std::string& old_name, std::string new_name);
  bool set_battery_charging(std::string& name, bool charging);
  bool enable_battery(std::string& name);
  bool disable_battery(std::string& name);

  bool add_solar_panel(std::string& name);
  bool add_solar_panel(SolarPanel&& newsolarpanel);
  bool remove_solar_panel(std::string& name);
  bool rename_solar_panel(std::string& old_name, std::string new_name);
  bool extract_solar_panel(std::string& name, uint8_t level);

  json serialize();
  
  //  [[nodiscard]] uint8_t get_extracted_solar_panels_cnt() const;nlohmann::
  [[nodiscard]] uint32_t get_solar_power_sum() const;
  
  void simulation_step();
};

#endif
