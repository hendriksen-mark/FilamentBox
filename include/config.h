#ifndef CONFIG_H
#define CONFIG_H

#pragma once

// Comment out to run with actual hardware, unncomment to run in MOCK mode.
//#define MOCK_MODE

// #define CHECK_TOLERANCE

// ============================================
// General Configuration
// ============================================
#ifndef BASE_PORT
#define BASE_PORT 80
#endif

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
#define FAN 14
#define HEATER_ACTIVE_LOW true

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

#ifndef SD_MISO_PIN
#define SD_MISO_PIN MISO
#endif
#ifndef SD_MOSI_PIN
#define SD_MOSI_PIN MOSI
#endif
#ifndef SD_SCLK_PIN
#define SD_SCLK_PIN SCK
#endif
#ifndef SD_CS_PIN
#define SD_CS_PIN 53
#endif

#define SLIDE_POT1 A10
#define SLIDE_POT2 A11
#define SLIDE_POT3 A12
#define SLIDE_POT4 A13

#define READINGS_PER_MINUTE 10
#define CALIBRATION_FILENAME "calibration.dat"
#define SETTINGS_FILENAME "settings.dat"

#define LOG_FILE_NAME "/log.txt"
#define LOG_MAX_FILE_SIZE_BYTES (1300 * 1024) // ~1.30 MB
#define MAX_UPLOAD_SIZE (300 * 1024)

// ============================================
// LOG Server Configuration
// ============================================
#define LOG_SERVER_PORT 2001
#define MAX_LOG_CONNECTIONS 1    // Log clients (reduced to fit socket limit)
#define LOG_CLIENT_TIMEOUT 60000 // 60 seconds in milliseconds (longer for log clients)

// ============================================
// NTP Time Configuration
// ============================================
#define NTP_ENABLED true            // Enable NTP time synchronization
#define NTP_SERVER "pool.ntp.org"   // NTP server to use
#define NTP_UPDATE_INTERVAL 3600000 // Update every hour (3600 seconds)
#define NTP_TIMEZONE_OFFSET 1       // UTC+1 for Netherlands (CET)
#define NTP_DST_OFFSET 1            // Additional hour for DST (CEST)
#define NTP_TIMEOUT 10000           // 10 second timeout for NTP requests


#endif
