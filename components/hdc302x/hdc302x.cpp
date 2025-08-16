#include "hdc302x.h"

#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hdc302x {

static const char *const TAG = "hdc302x";

void HDC302XComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up HDC3020...");
  // Soft reset
  if (!this->write_bytes(0x30, {0xA2})) {
    ESP_LOGD(TAG, "HDC3020 soft reset failed");
    this->mark_failed();
    return;
  }

  delay(5);

  // Start periodic measurement at 1 measurement per second
  if (!this->write_bytes(0x21, {0x30})) {
    ESP_LOGD(TAG, "Failed to start periodic measurement");
    this->mark_failed();
    return;
  }

  delay(10);

  ESP_LOGCONFIG(TAG, "HDC3020 auto measurement started at 1 Hz");
}

void HDC302XComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "HDC302x:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
  }
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "Temperature", this->temperature_);
  LOG_SENSOR("  ", "Humidity", this->humidity_);
}

void HDC302XComponent::update() {
  uint16_t raw_temperature, raw_humidity;

  if (!this->read_data(raw_temperature, raw_humidity)) {
    ESP_LOGD(TAG, "Failed to read sensor data");
    return;
  }

  // Convert raw values to actual temperature and humidity
  float temperature = -40.0f + 165.0f * (raw_temperature / 65535.0f);
  float humidity = 100.0f * (raw_humidity / 65535.0f);

  ESP_LOGD(TAG, "Got temperature=%.1f°C humidity=%.1f%%", temperature,
           humidity);
  if (this->temperature_ != nullptr)
    this->temperature_->publish_state(temperature);
  if (this->humidity_ != nullptr) this->humidity_->publish_state(humidity);
}

float HDC302XComponent::get_setup_priority() const {
  return setup_priority::DATA;
}

bool HDC302XComponent::read_data(uint16_t &temperature, uint16_t &humidity) {
  // For auto measurement mode, read the latest data using fetch command
  if (!this->write_bytes(0xE0, {0x00})) {
    ESP_LOGW(TAG, "Failed to send fetch command");
    return false;
  }

  delay(1);

  // Read 6 bytes of data
  uint8_t data[6];
  if (!this->read_bytes_raw(data, 6)) {
    ESP_LOGE(TAG, "Failed to read measurement data");
    return false;
  }

  // Extract temperature and humidity values
  temperature = (data[0] << 8) | data[1];
  humidity = (data[3] << 8) | data[4];

  return true;
}

}  // namespace hdc302x
}  // namespace esphome