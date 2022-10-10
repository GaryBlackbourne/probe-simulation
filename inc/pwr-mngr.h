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

  void simulation_step();
};

#endif
