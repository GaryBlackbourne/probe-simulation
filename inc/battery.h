#ifndef _BATTERY_H
#define _BATTERY_H

#include <stdint.h>

#define BATTERY_MAX_PWR_OUTPUT 50

class Battery{
private:

  uint32_t charge_level; // 0 < x < 1 000 000
  bool charging;

  bool enabled;

public:

  Battery();
  ~Battery();

  void enable();
  void disable();

  void charge();
  void stop_charge();
  [[nodiscard]] bool is_charging() const;

  [[nodiscard]] bool is_enabled() const ;

  void simulation_step(uint8_t, uint8_t);
};

#endif
