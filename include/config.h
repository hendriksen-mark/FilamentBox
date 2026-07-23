#ifndef CONFIG_H
#define CONFIG_H

#pragma once

// Comment out to run with actual hardware, unncomment to run in MOCK mode.
// #define MOCK_MODE
// #define DEBUG_MODE

// #define CHECK_TOLERANCE

#define COMMAND_MAX_SIZE 25
#define RESPONSE_MAX_SIZE 10

#define OLED_RESET 16 // Pin 15 -RESET digital signal
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

#define DHTTYPE DHT22

#define DHTPIN 2
#define HEATER 3

#define SCALE1_DOUT 4
#define SCALE1_CLK 5

#define SCALE2_DOUT 6
#define SCALE2_CLK 7

#define SCALE3_DOUT 8
#define SCALE3_CLK 9

#define SCALE4_DOUT 10
#define SCALE4_CLK 11

#define ROT1_DT A0
#define ROT1_CLK A1
#define ROT1_SW 22

#define ROT2_DT A2
#define ROT2_CLK A3
#define ROT2_SW 24

#define ROT3_DT A6
#define ROT3_CLK A7
#define ROT3_SW 26

#define ROT4_DT A8
#define ROT4_CLK A9
#define ROT4_SW 28

#define LCD_SDA 20
#define LCD_SCL 21

#define SD_MISO 50
#define SD_MOSI 51
#define SD_SCLK 52
#ifndef SD_CS
#define SD_CS 53
#endif

#define SLIDE_POT1 A10
#define SLIDE_POT2 A11
#define SLIDE_POT3 A12
#define SLIDE_POT4 A13

#define READINGS_PER_MINUTE 10
#define CALIBRATION_FILENAME "calibration.dat"
#define SETTINGS_FILENAME "settings.dat"

#endif
