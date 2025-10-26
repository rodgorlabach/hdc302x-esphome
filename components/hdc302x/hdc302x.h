#include "esphome.h"

class HDC3022Component : public PollingComponent, public i2c::I2CDevice {
 public:
  Sensor *temperature_sensor = nullptr;
  Sensor *humidity_sensor = nullptr;

  void set_temperature_sensor(Sensor *sensor) { temperature_sensor = sensor; }
  void set_humidity_sensor(Sensor *sensor) { humidity_sensor = sensor; }

  HDC3022Component() : PollingComponent(5000) {}

  void setup() override {
    // Nothing special on setup
  }

  void update() override {
    uint8_t command[2] = {0x24, 0x00};
    write(command, 2);
    delay(50);

    uint8_t data[6];
    if (read(data, 6) != i2c::ERROR_OK) {
      ESP_LOGW("hdc3022", "I2C read failed!");
      return;
    }

    uint16_t raw_temp = (data[0] << 8) | data[1];
    uint16_t raw_hum = (data[3] << 8) | data[4];

    float temperature = ((float)raw_temp * 165.0f / 65535.0f) - 40.0f;
    float humidity = ((float)raw_hum * 100.0f / 65535.0f);

    if (temperature_sensor)
      temperature_sensor->publish_state(temperature);
    if (humidity_sensor)
      humidity_sensor->publish_state(humidity);
  }
};
