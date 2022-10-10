#ifndef _SOLAR_PANEL_H
#define _SOLAR_PANEL_H

#include "stdint.h"

class SolarPanel{
private:
  uint8_t pwr_out;
  bool extracted;
public:
  SolarPanel();
  ~SolarPanel();

  void extract_solar_panel();
  void retract_solar_panel();
};

#endif
