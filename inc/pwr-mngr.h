#ifndef _PWR_MNGR_H
#define _PWR_MNGR_H

#include <stdint.h>
#include <stdbool.h>

#include "battery.h"
#include "solar-panel.h"

class PowerManager{
private:

  Battery battery2;
  Battery battery1;

  SolarPanel solar_panel;

public:

  PowerManager();
  ~PowerManager();

  [[nodiscard]] uint8_t get_active_batteries_cnt() const;
  [[nodiscard]] uint8_t get_charging_batteries_cnt() const;
  [[nodiscard]] uint8_t get_online_batteries_cnt() const;

  void simulation_step(uint8_t);
};

#endif
