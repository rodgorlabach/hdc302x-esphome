
This ESPHome external component enables support for **TI HDC3020, HDC3021, and HDC3022** temperature and humidity sensors.

### Installation

```yaml
external_components:
  - source: github://rodgorlabach/hdc3022-esphome
    components: [hdc3022]
```
### Configuration Example

```yaml
sensor:
  - platform: hdc3022
    update_interval: 60s
    address: 0x44
    temperature:
      name: "HDC3022 Temperature"
      id: hdc3022_temperature
    humidity:
      name: "HDC3022 Humidity"
      id: hdc3022_humidity
```
