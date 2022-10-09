#ifndef _PWR_MNGR_H
#define _PWR_MNGR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Battery{
  uint8_t pwr_out;
  uint8_t pwr_in;
  uint32_t charge_level; // 0 < x < 1 000 000
  bool charging;
} Battery;

typedef struct SolarPanel{
  uint8_t pwr_out;
  bool extracted;
} SolarPanel;

typedef struct PowerManager{
  Battery battery2;
  Battery battery1;
  SolarPanel solar_panel;
} PowerManager;


PowerManager pwr_mngr_simulation_step(PowerManager*, uint8_t);

#endif
