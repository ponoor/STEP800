# STEP800
8-axis stepper motor driver for Open Sound Control

![step800_r1_1](https://user-images.githubusercontent.com/1097902/131634424-28f9508c-f418-4d1a-af06-ffac0bb8adc5.JPG)

STEP800 is a 8-axis stepper motor driver designed for art or design projects. STEP800 combines the following elements into one single board:

- [Arduino Zero](https://www.arduino.cc/en/Guide/ArduinoZero)
- Ethernet shield
- 8 stepper motor drivers
- Sensor inputs for homing

The current firmware is focused on working with [Open Sound Control](http://opensoundcontrol.org/) (OSC) via Ethernet, which is a common protocol for creative coding environments, like openFrameworks, Processing, Max, Unity, or Touch Designer.

Stepper driver chips are STMicroelectronics's [L6470](https://www.st.com/en/motor-drivers/l6470.html) which provide most of functionalities as a stepper driver.


Friend of STEP800 : [STEP400](https://github.com/ponoor/STEP400)

## Documentation
https://ponoor.com/en/docs/step-series/

Forum: https://github.com/ponoor/step-series-support/discussions

## Repository Contents
### Firmware
These 2 folders contain same codes.
- [/STEP800_firmware](https://github.com/ponoor/STEP800/tree/main/STEP800_firmware) : Arduino Sketch folder
- [/firmware-platformIO/STEP800_firmware](https://github.com/ponoor/STEP800/tree/main/firmware-platformIO/STEP800_firmware) : PlatformIO folder

Note: We are working on the "[Universal Firmware](https://github.com/ponoor/step-series-universal-firmware)" which covers all STEP series board. A development of each firmware (above) will be terminated soon.

### Hardware
[/hardware](https://github.com/ponoor/STEP800/tree/main/hardware) : Eagle design files, BOM lists, and a schematics PDF

### Others
[/configTool](https://github.com/ponoor/STEP800/tree/main/configTool) : The configuration tool consists of a html and JavaScritpts.

## Firmware dependency
- **[OSC Library](https://github.com/CNMAT/OSC)** from CNMAT
- **[Ponoor L6470 Library](https://github.com/ponoor/Ponoor_L6470_Library)**
- **[ArduinoJSON Library](https://arduinojson.org/)**
- **[Adafruit SleepyDog Arduino Library](https://github.com/adafruit/Adafruit_SleepyDog)**


