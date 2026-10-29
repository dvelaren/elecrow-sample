# Elecrow 7inch DIS08070 Sample Code

This repository contains sample Arduino ESP32 code for the Elecrow 7inch DIS08070 display module. The code is designed to help users quickly set up and test the display functionality.

## Hardware Required

- [Elecrow 7inch DIS08070 display module](https://www.elecrow.com/esp32-display-7-inch-hmi-display-rgb-tft-lcd-touch-screen-support-lvgl.html)

## Software Required

- [Squareline Studio](https://squareline.io/)
- [Arduino IDE v2.x](https://www.arduino.cc/en/software)
- [ESP32 Board Package v3.2.1](https://github.com/espressif/arduino-esp32)
- [LVGL Library v8.3.11](https://github.com/lvgl/lvgl)
- [PCA9957](https://github.com/maxpromer/PCA9557-arduino)
- [LovyanGFX](https://github.com/lovyan03/LovyanGFX)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)

## Setup

1. Copy [lv_conf.h](config/lv_conf.h) file into the Arduino libraries folder.

   For Windows: `📂C:\Users\YOUR_USER\Documents\Arduino\libraries`

   For Linux: `📂/home/YOUR_USER/Arduino/libraries`

2. Design your LVGL user interface using Squareline Studio (SLS) and make sure to select as Hardware the Elecrow DIS08070 display.

3. Export UI files from SLS to UI folder using Flat Export configuration, then copy all the files where the .ino file is located.

4. Compile and test the code in Arduino IDE.
