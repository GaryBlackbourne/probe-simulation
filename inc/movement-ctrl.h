#ifndef _MOVEMENT_CTRL_H
#define _MOVEMENT_CTRL_H

#include <stdint.h>

typedef struct Thruster{
  int64_t thrust;
  uint32_t power_consumption;
} Thruster;

typedef struct MovementControl{
  Thruster main_engine;
  Thruster break_engine;
  Thruster rotational_engines;
} MovementControl;

#endif
