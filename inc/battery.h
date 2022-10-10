#ifndef _BATTERY_H
#define _BATTERY_H

#include <stdint.h>

class Battery{
private:
  uint8_t pwr_out;
  uint8_t pwr_in;
  uint32_t charge_level; // 0 < x < 1 000 000
  bool charging;
  bool enabled;
public:
  Battery();
  ~Battery();

  void enable();
  void disable();

  [[nodiscard]] bool is_enabled() const ;
};

#endif