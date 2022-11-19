#ifndef _BATTERY_H
#define _BATTERY_H

#define BATTERY_MAX_PWR_OUTPUT 50
#define BATTERY_MAX_CHARGE_LEVEL 1000000

#include <stdint.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

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
  [[nodiscard]] bool is_enabled() const;
  [[nodiscard]] bool is_active() const;

  uint8_t charge(uint8_t);
  uint8_t discharge(uint8_t);

  json serialize();
  
  void simulation_step(uint8_t, uint8_t);
};

#endif
