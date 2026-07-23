#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once

#include "config.h"

#ifndef MOCK_MODE
#include <ClickEncoder.h>
#include <HX711.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_GFX.h"

extern Adafruit_SSD1306 display;

extern HX711 scale1;
extern HX711 scale2;
extern HX711 scale3;
extern HX711 scale4;

extern ClickEncoder *encoder1;
extern ClickEncoder *encoder2;
extern ClickEncoder *encoder3;
extern ClickEncoder *encoder4;

#else
#include "mock_data.h"
#endif

extern int maxHumidity;
extern int maxTemp;

extern int toleranceMin1;
extern int toleranceMax1;
extern int toleranceMin2;
extern int toleranceMax2;
extern int toleranceMin3;
extern int toleranceMax3;
extern int toleranceMin4;
extern int toleranceMax4;
extern bool out_of_tolerance1;
extern bool out_of_tolerance2;
extern bool out_of_tolerance3;
extern bool out_of_tolerance4;

extern float scale1_calibration_factor;
extern float scale2_calibration_factor;
extern float scale3_calibration_factor;
extern float scale4_calibration_factor;

extern float w1;
extern float w2;
extern float w3;
extern float w4;

extern float l1;
extern float l2;
extern float l3;
extern float l4;

extern int b1;
extern int b2;
extern int b3;
extern int b4;

extern int pot1;
extern int pot2;
extern int pot3;
extern int pot4;

extern float currentHumidity;
extern float currentTemp;

extern bool heaterPowerOn;
extern bool writingToSerial;

#endif // GLOBALS_H
