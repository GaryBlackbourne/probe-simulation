#ifndef _ROVER_MODEL_H
#define _ROVER_MODEL_H

#include <stdint.h>
#include <stdbool.h>

#include "pos-sys.h"
#include "pwr-mngr.h"

typedef struct Probe{
  PowerManager pwr_manager;
  PositioningSystem POS_system;
} Probe;

// event functions

#endif
