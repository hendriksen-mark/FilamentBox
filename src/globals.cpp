#include "globals.h"

int maxHumidity = 5;
int maxTemp = 80;

int toleranceMin1 = 256;
int toleranceMax1 = 768;
int toleranceMin2 = 256;
int toleranceMax2 = 768;
int toleranceMin3 = 256;
int toleranceMax3 = 768;
int toleranceMin4 = 256;
int toleranceMax4 = 768;

bool out_of_tolerance1 = false;
bool out_of_tolerance2 = false;
bool out_of_tolerance3 = false;
bool out_of_tolerance4 = false;

float scale1_calibration_factor = -421000;
float scale2_calibration_factor = -421000;
float scale3_calibration_factor = -421000;
float scale4_calibration_factor = -421000;

float w1 = 0.00;
float w2 = 0.00;
float w3 = 0.00;
float w4 = 0.00;

float l1 = 0.00;
float l2 = 0.00;
float l3 = 0.00;
float l4 = 0.00;

int b1 = -1;
int b2 = -1;
int b3 = -1;
int b4 = -1;

int pot1 = -1;
int pot2 = -1;
int pot3 = -1;
int pot4 = -1;

float currentHumidity = 0.00;
float currentTemp = 0.00;

bool heaterPowerOn = false;
bool writingToSerial = false;

#ifndef MOCK_MODE
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

ClickEncoder *encoder1;
ClickEncoder *encoder2;
ClickEncoder *encoder3;
ClickEncoder *encoder4;
#endif
