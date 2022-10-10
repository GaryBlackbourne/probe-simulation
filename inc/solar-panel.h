#ifndef _SOLAR_PANEL_H
#define _SOLAR_PANEL_H

#include "stdint.h"

#define MAX_PWR_OUT  100

class SolarPanel{
private:

  uint8_t pwr_out;

  bool extracted;

public:

  SolarPanel();
  ~SolarPanel();

  void extract_solar_panel();
  void retract_solar_panel();

  uint8_t get_power() const;
};

#endif
