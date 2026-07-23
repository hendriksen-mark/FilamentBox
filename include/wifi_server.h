#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#pragma once

#include <DNSServer.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>

#include "log_server.h"
#include "custom_log.h"
#include "functions.h"
#include "config.h"

void ESP_Server_setup();
void ota_setup();
void wifi_loop();

#endif // WIFI_SERVER_H
