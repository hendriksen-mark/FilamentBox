#include <TimerOne.h>
#include "config.h"
#include "custom_log.h"
#include "ntp_client.h"
#include "functions.h"
#include "globals.h"
#include "climate.h"

#ifdef MOCK_MODE
#include "mock_data.h"
#endif

#ifndef MOCK_MODE
void timerIsr()
{
  encoder1->service();
  encoder2->service();
  encoder3->service();
  encoder4->service();
}
#endif

void calibrationWrite(const __FlashStringHelper *msg)
{
  writingToSerial = true;
  Serial.print(F("CALIBRATION:"));
  Serial.print(scale1_calibration_factor);
  Serial.print(F(" "));
  Serial.print(scale2_calibration_factor);
  Serial.print(F(" "));
  Serial.print(scale3_calibration_factor);
  Serial.print(F(" "));
  Serial.print(scale4_calibration_factor);
  Serial.print(F(":"));
  Serial.println(msg);
  writingToSerial = false;
}

void calibrationDataWrite(const __FlashStringHelper *msg, long data)
{
  writingToSerial = true;
  Serial.print(F("CALIBRATION:"));
  Serial.print(scale1_calibration_factor);
  Serial.print(F(" "));
  Serial.print(scale2_calibration_factor);
  Serial.print(F(" "));
  Serial.print(scale3_calibration_factor);
  Serial.print(F(" "));
  Serial.print(scale4_calibration_factor);
  Serial.print(F(":"));
  Serial.print(msg);
  Serial.println(data);
  writingToSerial = false;
}

void safeWrite(const __FlashStringHelper *msg, char *data)
{
  while (writingToSerial)
  {
    delay(5);
  }
  writingToSerial = true;
  Serial.print(msg);
  Serial.println(data);
  writingToSerial = false;
}

#if !defined(MOCK_MODE) || defined(USE_LITTLEFS)

bool saveConfig()
{
  REMOTE_LOG_DEBUG("save config");
  JsonDocument json;
  json["maxHumidity"] = maxHumidity;
  json["maxTemp"] = maxTemp;
  json["toleranceMin1"] = toleranceMin1;
  json["toleranceMax1"] = toleranceMax1;
  json["toleranceMin2"] = toleranceMin2;
  json["toleranceMax2"] = toleranceMax2;
  json["toleranceMin3"] = toleranceMin3;
  json["toleranceMax3"] = toleranceMax3;
  json["toleranceMin4"] = toleranceMin4;
  json["toleranceMax4"] = toleranceMax4;
  json["scale1_calibration_factor"] = scale1_calibration_factor;
  json["scale2_calibration_factor"] = scale2_calibration_factor;
  json["scale3_calibration_factor"] = scale3_calibration_factor;
  json["scale4_calibration_factor"] = scale4_calibration_factor;

  return writeJsonFile(CALIBRATION_FILENAME, json);
}


bool loadConfig()
{
  REMOTE_LOG_DEBUG("load config");
  JsonDocument json;
  if (!readJsonFile(CALIBRATION_FILENAME, json))
  {
    REMOTE_LOG_DEBUG("Create new file with default values");
		return saveConfig();
  }
  maxHumidity = json["maxHumidity"];
  maxTemp = json["maxTemp"];
  toleranceMin1 = json["toleranceMin1"];
  toleranceMax1 = json["toleranceMax1"];
  toleranceMin2 = json["toleranceMin2"];
  toleranceMax2 = json["toleranceMax2"];
  toleranceMin3 = json["toleranceMin3"];
  toleranceMax3 = json["toleranceMax3"];
  toleranceMin4 = json["toleranceMin4"];
  toleranceMax4 = json["toleranceMax4"];
  scale1_calibration_factor = json["scale1_calibration_factor"];
  scale2_calibration_factor = json["scale2_calibration_factor"];
  scale3_calibration_factor = json["scale3_calibration_factor"];
  scale4_calibration_factor = json["scale4_calibration_factor"];
  return true;
}
#endif

void report(void)
{
  REMOTE_LOG_DEBUG(F("DEBUG: Begin report"));

#ifndef MOCK_MODE
  float w1 = scale1.get_units();
  float w2 = scale2.get_units();
  float w3 = scale3.get_units();
  float w4 = scale4.get_units();
#endif

  // Report to Serial
  while (writingToSerial)
  {
    delay(3);
  }
  writingToSerial = true;
  Serial.print(F("H:"));
  Serial.print(currentHumidity);
  Serial.print(F("% T:"));
  Serial.print(currentTemp);
  Serial.print(F("C S1:"));
  Serial.print(w1);
  Serial.print(F("kg S2:"));
  Serial.print(w2);
  Serial.print(F("kg S3:"));
  Serial.print(w3);
  Serial.print(F("kg S4:"));
  Serial.print(w4);
  Serial.print(F("kg L1:"));
  Serial.print(l1);
  Serial.print(F("mm L2:"));
  Serial.print(l2);
  Serial.print(F("mm L3:"));
  Serial.print(l3);
  Serial.print(F("mm L4:"));
  Serial.print(l4);
  Serial.print(F("mm P:"));
  Serial.print(heaterPowerOn ? F("ON") : F("OFF"));
  writingToSerial = false;

#ifndef MOCK_MODE
  // update LCD
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(currentHumidity, 1);
  display.print(F("%"));
  display.print(currentTemp, 1);
  display.println(F("C"));

  display.setTextSize(1);
  display.setCursor(0, 16);
  if (out_of_tolerance1)
  {
    display.print(F("1! "));
  }
  else
  {
    display.print(F("1  "));
  }
  display.print(w1);
  display.print(F("kg "));
  display.print(l1, 1);
  display.print(F("mm"));

  display.setCursor(0, 26);
  if (out_of_tolerance2)
  {
    display.print(F("2! "));
  }
  else
  {
    display.print(F("2  "));
  }
  display.print(w2);
  display.print(F("kg "));
  display.print(l2, 1);
  display.print(F("mm"));

  display.setCursor(0, 36);
  if (out_of_tolerance3)
  {
    display.print(F("3! "));
  }
  else
  {
    display.print(F("3  "));
  }
  display.print(w3);
  display.print(F("kg "));
  display.print(l3, 1);
  display.print(F("mm"));

  display.setCursor(0, 46);
  if (out_of_tolerance4)
  {
    display.print(F("4! "));
  }
  else
  {
    display.print(F("4  "));
  }
  display.print(w4);
  display.print(F("kg "));
  display.print(l4, 1);
  display.print(F("mm"));

  display.setCursor(15, 56);
  if (heaterPowerOn)
  {
    display.println(F("Heater Power:  ON"));
  }
  else
  {
    display.println(F("Heater Power: OFF"));
  }

  display.display();
#endif

  REMOTE_LOG_DEBUG(F("DEBUG: End report"));
}

String prompt(String msg)
{
  writingToSerial = true;
  Serial.print(F("PROMPT:"));
  Serial.println(msg);
  writingToSerial = false;

  while (true)
  {
    if (Serial.available() > 0)
    {
      char input[RESPONSE_MAX_SIZE + 1];
      byte size = Serial.readBytes(input, RESPONSE_MAX_SIZE);
      input[size] = 0;
      REMOTE_LOG_DEBUG(F("DEBUG: input[]="), input);
      return String(input);
    }
    delay(10);
  }
}

float getCalibrationValue(int scaleNum)
{
  switch (scaleNum)
  {
  case 1:
    return scale1_calibration_factor;
  case 2:
    return scale2_calibration_factor;
  case 3:
    return scale3_calibration_factor;
  case 4:
    return scale4_calibration_factor;
  default:
    return 0;
  }
}

void setCalibrationValue(int scaleNum, float newValue)
{
  switch (scaleNum)
  {
  case 1:
    scale1_calibration_factor = newValue;
    break;
  case 2:
    scale2_calibration_factor = newValue;
    break;
  case 3:
    scale3_calibration_factor = newValue;
    break;
  case 4:
    scale4_calibration_factor = newValue;
    break;
  }
#ifndef MOCK_MODE
  saveConfig();
#endif
}

void calibrate(int scaleNum)
{
  Timer1.stop();
  calibrationWrite(F("Entering calibration mode..."));
#ifndef MOCK_MODE

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Calibrate"));
  display.print(F("Scale "));
  display.println(scaleNum);
  display.display();

  HX711 scale;
  switch (scaleNum)
  {
  case 1:
    scale = scale1;
    break;
  case 2:
    scale = scale2;
    break;
  case 3:
    scale = scale3;
    break;
  case 4:
    scale = scale4;
    break;
  default:
    safeWrite(F("ERROR: Bad Scale: "), (char *)String(scaleNum).c_str());
    Timer1.start();
    return;
  }
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
#else
  long zero_factor = 0;
#endif
  calibrationDataWrite(F("Zero Factor = "), zero_factor);
  delay(1000);
  String answer = prompt(String(F("Place known weight on scale. Enter weight (in kg) and click OK.")));

  REMOTE_LOG_DEBUG(F("DEBUG: String answer="), answer);
  if (strcmp(answer.c_str(), "CANCEL") == 0)
  {
    calibrationWrite(F("Calibration canceled."));
    Timer1.start();
    return;
  }
  float targetKg = atof(answer.c_str());
  calibrationDataWrite(F("Calibration grams = "), targetKg * 1000);

#ifndef MOCK_MODE
  float currentCalibrationFactor = getCalibrationValue(scaleNum);
  scale.set_scale(currentCalibrationFactor);
  float currentReading = scale.get_units();
  while (currentReading != targetKg)
  {
    String promptMsg(F("Enter new Calibration value and click OK. Current reading is "));
    promptMsg += String(currentReading, 4);
    promptMsg += '/';
    promptMsg += String(targetKg, 4);
    promptMsg += String(F(" Current Calibration Value is "));
    promptMsg += String(currentCalibrationFactor);
    answer = prompt(promptMsg);

    if (strcmp(answer.c_str(), "CANCEL") == 0)
    {
      calibrationWrite(F("Calibration canceled."));
      Timer1.start();
      return;
    }
    else if (strcmp(answer.c_str(), "ACCEPT") == 0)
    {
      setCalibrationValue(scaleNum, currentCalibrationFactor);
      calibrationWrite(F("Calibration complete."));
      Timer1.start();
      return;
    }
    else
    {
      currentCalibrationFactor = atof(answer.c_str());
      scale.set_scale(currentCalibrationFactor);
      currentReading = scale.get_units();
    }
  }
#else
  delay(2000);
#endif
  calibrationWrite(F("Target matched. Calibration complete."));
  Timer1.start();
}

void setup()
{
  Serial.begin(115200);
  REMOTE_LOG_INFO("Start ESP32");
  ChangeNeoPixels_info();
  infoLedFadeIn(white, 500); // Smooth startup indication
  serialWait();
  functions_setup();
  delay(200);

  ESP_Server_setup();
  initializeLogServer();
  initializeNTP();
  ota_setup();

#ifndef MOCK_MODE
  display.begin();
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Booting..."));
  display.setTextSize(1);
  display.setCursor(20, 40);
  display.println(F("Please Wait..."));
  display.display();

  loadConfig();

  pinMode(HEATER, OUTPUT);
  pinMode(SLIDE_POT1, INPUT);
  pinMode(SLIDE_POT2, INPUT);
  pinMode(SLIDE_POT3, INPUT);
  pinMode(SLIDE_POT4, INPUT);

  setupDHTSensor();

  scale1.begin(SCALE1_DOUT, SCALE1_CLK);
  scale1.set_scale(scale1_calibration_factor);
  scale1.tare();

  scale2.begin(SCALE2_DOUT, SCALE2_CLK);
  scale2.set_scale(scale2_calibration_factor);
  scale2.tare();

  scale3.begin(SCALE3_DOUT, SCALE3_CLK);
  scale3.set_scale(scale3_calibration_factor);
  scale3.tare();

  scale4.begin(SCALE4_DOUT, SCALE4_CLK);
  scale4.set_scale(scale4_calibration_factor);
  scale4.tare();

  encoder1 = new ClickEncoder(ROT1_CLK, ROT1_DT, ROT1_SW);
  encoder2 = new ClickEncoder(ROT2_CLK, ROT2_DT, ROT2_SW);
  encoder3 = new ClickEncoder(ROT3_CLK, ROT3_DT, ROT3_SW);
  encoder4 = new ClickEncoder(ROT4_CLK, ROT4_DT, ROT4_SW);
  encoder1->setAccelerationEnabled(false);
  encoder2->setAccelerationEnabled(false);
  encoder3->setAccelerationEnabled(false);
  encoder4->setAccelerationEnabled(false);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);

#else
  REMOTE_LOG_INFO("MOCK_MODE: Using mock data for testing.");
  mock();
#endif
  Serial.println(F("INFO:Waiting on Sensors to warm up before beginning..."));
  delay(10000);
  Serial.println(F("INFO:Sensors ready."));
  Timer1.initialize(60000000 / READINGS_PER_MINUTE);
  Timer1.attachInterrupt(report);
  Timer1.attachInterrupt(readDHTSensor);
  Timer1.initialize(NTP_UPDATE_INTERVAL);
  Timer1.attachInterrupt(handleNTPUpdate);

}

void loop()
{
  wifi_loop();
  yield(); // Prevent watchdog reset - allows ESP32 to handle WiFi/background tasks
#ifndef MOCK_MODE
#ifdef CHECK_TOLERANCE
  pot1 = analogRead(SLIDE_POT1);
  if (pot1 < toleranceMin1)
  {
    Serial.println(F("TOLERANCE: Sensor 1 below Minimum!"));
    out_of_tolerance1 = true;
  }
  else if (pot1 > toleranceMax1)
  {
    Serial.println(F("TOLERANCE: Sensor 1 above Maximum!"));
    out_of_tolerance1 = true;
  }
  else
  {
    out_of_tolerance1 = false;
  }

  pot2 = analogRead(SLIDE_POT2);
  if (pot2 < toleranceMin2)
  {
    Serial.println(F("TOLERANCE: Sensor 2 below Minimum!"));
    out_of_tolerance2 = true;
  }
  else if (pot2 > toleranceMax2)
  {
    Serial.println(F("TOLERANCE: Sensor 2 above Maximum!"));
    out_of_tolerance2 = true;
  }
  else
  {
    out_of_tolerance2 = false;
  }

  pot3 = analogRead(SLIDE_POT3);
  if (pot3 < toleranceMin3)
  {
    Serial.println(F("TOLERANCE: Sensor 3 below Minimum!"));
    out_of_tolerance3 = true;
  }
  else if (pot3 > toleranceMax3)
  {
    Serial.println(F("TOLERANCE: Sensor 3 above Maximum!"));
    out_of_tolerance3 = true;
  }
  else
  {
    out_of_tolerance3 = false;
  }

  pot4 = analogRead(SLIDE_POT4);
  if (pot4 < toleranceMin4)
  {
    Serial.println(F("TOLERANCE: Sensor 4 below Minimum!"));
    out_of_tolerance4 = true;
  }
  else if (pot4 > toleranceMax4)
  {
    Serial.println(F("TOLERANCE: Sensor 4 above Maximum!"));
    out_of_tolerance4 = true;
  }
  else
  {
    out_of_tolerance4 = false;
  }
#endif
  l1 += encoder1->getAccumulate();
  b1 = encoder1->getButton();
  if (b1 == Button::DoubleClicked)
  {
    l1 = 0.00;
  }

  l2 += encoder2->getAccumulate();
  b2 = encoder2->getButton();
  if (b2 == Button::DoubleClicked)
  {
    l2 = 0.00;
  }

  l3 += encoder3->getAccumulate();
  b3 = encoder3->getButton();
  if (b3 == Button::DoubleClicked)
  {
    l3 = 0.00;
  }

  l4 += encoder4->getAccumulate();
  b4 = encoder4->getButton();
  if (b4 == Button::DoubleClicked)
  {
    l4 = 0.00;
  }
#endif
  if (Serial.available() > 0)
  {
    char input[COMMAND_MAX_SIZE + 1];
    // Get next command from Serial (add 1 for final 0)
    byte size = Serial.readBytes(input, COMMAND_MAX_SIZE);
    // Add the final 0 to end the C string
    input[size] = 0;

    char *command = strtok(input, " ");
    if (command != 0)
    {
      if (strcmp(command, "SET") == 0)
      {
        // Get the next part
        command = strtok(0, " ");
        // Split the command in two values
        char *separator = strchr(command, '=');
        if (separator != 0)
        {
          // Actually split the string in 2: replace '=' with 0
          *separator = 0;
          char *setting = command;
          ++separator;
          int newValue = atoi(separator);
          bool badSetting = false;
          if (strcmp(setting, "T") == 0)
          {
            maxTemp = newValue;
          }
          else if (strcmp(setting, "H") == 0)
          {
            maxHumidity = newValue;
          }
          else if (strcmp(setting, "TOL-MIN1") == 0)
          {
            toleranceMin1 = newValue;
          }
          else if (strcmp(setting, "TOL-MAX1") == 0)
          {
            toleranceMax1 = newValue;
          }
          else if (strcmp(setting, "TOL-MIN2") == 0)
          {
            toleranceMin2 = newValue;
          }
          else if (strcmp(setting, "TOL-MAX2") == 0)
          {
            toleranceMax2 = newValue;
          }
          else if (strcmp(setting, "TOL-MIN3") == 0)
          {
            toleranceMin3 = newValue;
          }
          else if (strcmp(setting, "TOL-MAX3") == 0)
          {
            toleranceMax3 = newValue;
          }
          else if (strcmp(setting, "TOL-MIN4") == 0)
          {
            toleranceMin4 = newValue;
          }
          else if (strcmp(setting, "TOL-MAX4") == 0)
          {
            toleranceMax4 = newValue;
          }
          else
          {
            safeWrite(F("ERROR: Bad Setting: "), setting);
            badSetting = true;
          }
          if (!badSetting)
          {
#ifndef MOCK_MODE

#endif
          }
        }
      }
      else if (strcmp(command, "TARE") == 0)
      {
        // Get the next part
        command = strtok(0, " ");
        if (strcmp(command, "1") == 0)
        {
#ifndef MOCK_MODE
          scale1.tare();
#endif
        }
        else if (strcmp(command, "2") == 0)
        {
#ifndef MOCK_MODE
          scale2.tare();
#endif
        }
        else if (strcmp(command, "3") == 0)
        {
#ifndef MOCK_MODE
          scale3.tare();
#endif
        }
        else if (strcmp(command, "4") == 0)
        {
#ifndef MOCK_MODE
          scale4.tare();
#endif
        }
        else
        {
          safeWrite(F("ERROR: Bad Scale Number: "), command);
        }
      }
      else if (strcmp(command, "ZERO") == 0)
      {
        // Get the next part
        command = strtok(0, " ");
        if (strcmp(command, "1") == 0)
        {
          l1 = 0.00;
        }
        else if (strcmp(command, "2") == 0)
        {
          l2 = 0.00;
        }
        else if (strcmp(command, "3") == 0)
        {
          l3 = 0.00;
        }
        else if (strcmp(command, "4") == 0)
        {
          l4 = 0.00;
        }
        else
        {
          safeWrite(F("ERROR: Bad Encoder Number: "), command);
        }
      }
      else if (strcmp(command, "CALI") == 0)
      {
        command = strtok(0, " ");
        calibrate(atoi(command));
      }
      else
      {
        safeWrite(F("ERROR: Bad Command: "), input);
      }
    }
  }
  delay(25);
}
