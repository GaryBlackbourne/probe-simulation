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

  void charge();
  void stop_charge();
  [[nodiscard]] bool is_charging() const;

  void set_pwr_in(uint8_t);
  void req_pwr_out(uint8_t);

  [[nodiscard]] bool is_enabled() const ;

  void simulation_step();
};

#endif
