#ifndef _POS_SYS_H
#define _POS_SYS_H

#include <stdint.h>

typedef struct GPS{
  uint32_t x;
  uint32_t y;
  uint32_t z;
} GPS;

typedef struct Direction{
  int32_t azimuth;
  int32_t elevation;
} Direction;

typedef struct PositioningSystem{
  uint8_t power_consumption;
  GPS gps_module;
  Direction direction;
} PositioningSystem;

#endif
