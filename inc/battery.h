#ifndef _BATTERY_H
#define _BATTERY_H

#include <cstdint>
#define BATTERY_MAX_PWR_OUTPUT 50
#define BATTERY_MAX_CHARGE_LEVEL 1000000

#include <stdint.h>
#include <string>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Battery{
private:

  uint32_t charge_level; // 0 < x < 1 000 000

  bool charging;
  bool enabled;

  std::string name;

public:

  Battery(std::string& name);
  Battery(std::string&& name);
  Battery(uint32_t charge_level, std::string& name);
  ~Battery();

  void enable();
  void disable();

  void charge();
  void stop_charge();

  [[nodiscard]] bool is_charging() const;
  [[nodiscard]] bool is_enabled() const;
  [[nodiscard]] bool is_active() const;

  uint32_t charge(uint32_t);
  uint32_t discharge(uint32_t);

  void set_name(std::string&& new_name);
  std::string get_name() const;

  json serialize() const;
  
};

#endif
