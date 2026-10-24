# OpenWatt Node

A PlatformIO simulation of energy telemetry for an ESP32-style board. The firmware generates synthetic watt readings, integrates simulated watt-hours, and prints JSON-like telemetry over serial.

## Hardware and safety notice

This project does not read a current transformer or any other sensor. It does not measure household electricity, implement Matter or ESPHome, or provide calibrated/safe metering. The firmware is a simulation only and must not be treated as mains-monitoring firmware. Do not connect it to mains wiring or use its output for electrical safety or billing decisions.

## Build and run

Requirements: PlatformIO Core.

```bash
pio run -e esp32dev
pio run -e native
```

The `esp32dev` environment prints simulated readings at 115200 baud. Tests exercise the independent watt clamp and energy accumulation calculations.

## Project files

- `src/main.cpp`: synthetic power sample loop.
- `test/test_energy.cpp`: native tests for the sample calculations.
- `platformio.ini`: ESP32 and native environments.

## License

Licensed under the [PolyForm Noncommercial License 1.0.0](LICENSE). This source-available license restricts commercial use; it is not an OSI-approved open-source license. See the license for terms and exceptions. Third-party dependencies retain their own licenses.
