#include "wifi_server.h"

void ESP_Server_setup()
{
	WiFiManager wm;
	WiFi.mode(WIFI_STA);
	wm.setDebugOutput(false);
	wm.setConfigPortalTimeout(120);

	bool res;
	res = wm.autoConnect(DEVICE_NAME);
	if (!res)
	{
		ESP.restart();
	}
	// Setup mDNS
	if (MDNS.begin(DEVICE_NAME))
	{
		REMOTE_LOG_DEBUG("mDNS responder started: ", DEVICE_NAME, ".local");
		MDNS.addService("http", "tcp", BASE_PORT);
	}
}

void ota_setup()
{
	ArduinoOTA
		.onStart([]()
				 {
			String type;
			if (ArduinoOTA.getCommand() == U_FLASH)
				type = "sketch";
			else // U_SPIFFS
				type = "filesystem";

			REMOTE_LOG_DEBUG("Start updating " + type); })
		.onEnd([]()
			   { REMOTE_LOG_DEBUG("End"); })
		.onProgress([](unsigned int progress, unsigned int total)
					{ REMOTE_LOG_INFO("Progress: " + String((progress / (total / 100))) + "%"); })
		.onError([](ota_error_t error)
				 {
			REMOTE_LOG_ERROR("Error[%u]: ", error);
			switch (error)
			{
			case OTA_AUTH_ERROR:
				REMOTE_LOG_ERROR("Auth Failed");
				break;
			case OTA_BEGIN_ERROR:
				REMOTE_LOG_ERROR("Begin Failed");
				break;
			case OTA_CONNECT_ERROR:
				REMOTE_LOG_ERROR("Connect Failed");
				break;
			case OTA_RECEIVE_ERROR:
				REMOTE_LOG_ERROR("Receive Failed");
				break;
			case OTA_END_ERROR:
				REMOTE_LOG_ERROR("End Failed");
				break;
			default:
				break;
			} })
		.setHostname(DEVICE_NAME)
		.begin();
}

void wifi_loop()
{
	ArduinoOTA.handle();

	// Handle incoming log client connections and client communication
	handleNewLogConnections();
	handleLogClientCommunication();
	cleanupLogClients();
}
