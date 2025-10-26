
This ESPHome external component enables support for **TI HDC3020, HDC3021, and HDC3022** temperature and humidity sensors.

### Installation

```yaml
external_components:
  - source: github://rodgorlabach/hdc302x-esphome
    components: [hdc302x]
```
### Configuration Example

```yaml
sensor:
  - platform: hdc302x
    update_interval: 60s
    address: 0x44
    temperature:
      name: "HDC302x Temperature"
      id: hdc302x_temperature
    humidity:
      name: "HDC302x Humidity"
      id: hdc302x_humidity
```
