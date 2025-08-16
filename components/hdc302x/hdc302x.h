#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace hdc302x {

class HDC302XComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void set_temperature(sensor::Sensor *temperature) {
    temperature_ = temperature;
  }

  void set_humidity(sensor::Sensor *humidity) { humidity_ = humidity; }

  void setup() override;

  void dump_config() override;

  void update() override;

  float get_setup_priority() const override;

  bool read_data(uint16_t &temperature, uint16_t &humidity);

 protected:
  sensor::Sensor *temperature_{nullptr};
  sensor::Sensor *humidity_{nullptr};
};

}  // namespace hdc302x
}  // namespace esphome