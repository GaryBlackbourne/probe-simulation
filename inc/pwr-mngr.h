#ifndef _PWR_MNGR_H
#define _PWR_MNGR_H

#include <stdint.h>
#include <stdbool.h>
#include <vector>

#include "battery.h"
#include "solar-panel.h"

class PowerManager{
private:

  std::vector<Battery> batteries;

  std::vector<SolarPanel> solar_panels;

public:

  PowerManager();
  ~PowerManager();

  [[nodiscard]] uint8_t get_active_batteries_cnt() const;
  [[nodiscard]] uint8_t get_charging_batteries_cnt() const;
  [[nodiscard]] uint8_t get_enabled_batteries_cnt() const;

  //  [[nodiscard]] uint8_t get_extracted_solar_panels_cnt() const;
  [[nodiscard]] uint8_t get_solar_power_sum() const;
  
  void simulation_step(uint8_t);
};

#endif
