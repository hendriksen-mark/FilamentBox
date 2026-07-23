#include "climate.h"

DHT dht(DHTPIN, DHTTYPE);

void setupDHTSensor()
{
    dht.begin();
}

void readDHTSensor()
{
#ifndef MOCK_MODE
    currentHumidity = dht.readHumidity();
    // Read temperature as Celsius
    currentTemp = dht.readTemperature();
#endif

    // Check if any reads failed and exit early (to try again).
    if (isnan(currentHumidity) || isnan(currentTemp))
    {
        REMOTE_LOG_ERROR(F("ERROR: Failed to read from DHT sensor!"));
        return;
    }

    if (currentTemp > maxTemp)
    {
        heaterPowerOn = false;
    }
    else
    {
        if (currentHumidity > maxHumidity)
        {
            heaterPowerOn = true;
        }
    }
    HeaterPowerWrite();
}

void HeaterPowerWrite()
{
#ifndef MOCK_MODE
    digitalWrite(HEATER, HEATER_ACTIVE_LOW ? !heaterPowerOn : heaterPowerOn);
#endif
}