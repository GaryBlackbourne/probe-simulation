#ifndef _ROVER_MODEL_H
#define _ROVER_MODEL_H

#include <stdint.h>
#include <stdbool.h>

// structural typedefs:

typedef struct Battery{
  uint8_t pwr_out;
  uint8_t pwr_in;
  uint32_t charge_level;
  bool charging;
}Battery;

typedef struct SolarPanel{
  uint8_t pwr_out;
  bool extracted;
}SolarPanel;

typedef struct PowerManager{
  Battery battery;
  SolarPanel solar_panel;
}PowerManager;

typedef struct Rover{
  PowerManager pwwr_manager;

}Rover;

// event functions

#endif
