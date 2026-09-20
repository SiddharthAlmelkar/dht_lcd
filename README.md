# ESP32 Combined DHT11 and Parallel LCD Project

An integrated embedded application written in C using the ESP-IDF framework. This project interfaces an ESP32 with a DHT11 environmental sensor and a standard 16x2 character LCD using an 8-bit parallel bus layout to dynamically print live temperature and humidity metrics.

## Circuit Configuration

### LCD Module Interfacing
* LCD Pin 1 (VSS) ➡️ GND Rail
* LCD Pin 2 (VDD) ➡️ ESP32 5V / Vin
* LCD Pin 3 (V0) ➡️ GND Rail (Maximum Contrast)
* LCD Pin 4 (RS) ➡️ ESP32 GPIO 4
* LCD Pin 5 (R/W) ➡️ GND Rail
* LCD Pin 6 (E) ➡️ ESP32 GPIO 18
* LCD Pins D0-D7 ➡️ ESP32 GPIOs [14, 27, 26, 25, 33, 32, 19, 13]

### DHT11 Sensor Interfacing
* VCC ➡️ ESP32 3.3V
* DATA ➡️ ESP32 GPIO 23
* GND ➡️ GND Rail

## Deployment
Build and flash using your standard development toolchain core environment. Data updates autonomously across the physical glass matrix pane layout every 2 seconds.
