#pragma once

#include <Arduino.h>
#include "WiFi.h"

/**
 * @class WiFiManager
 * @brief A utility class to manage Wi-Fi connections on ESP32 board.
 * 
 * The WiFiManager class simplifies the use of the Arduino `WiFi` library by providing:
 * - Wi-Fi module initialization (`begin`)
 * - Network scanning with formatted output (`scan`)
 * - Interactive SSID/password input for WiFi connection (`connectInteractively`)
 * - Predefined connection by SSID or index (`connect`, `connectByIndex`)
 * 
 * @note `begin()` must be called inside `setup()` to ensure Wi-Fi hardware is ready.
 * 
 * example:
 * ```
 * WiFiManager wifi;
 * wifi.begin();
 * wifi.scan();
 * wifi.connectInteractively();
 * ```
 * 
 */
class WiFiManager {
public:
  WiFiManager();
  void setTimeout(int millis);
  
  int scan();
  
  wl_status_t reconnect();
  wl_status_t connectInteractively();
  wl_status_t connectByIndex(int idx, String password);
  wl_status_t connect(String ssid, String password);
  wl_status_t getStatus();
  String getIPAddress();

private:
  String getInput(String msg);
  String getWiFiAuthMode(wifi_auth_mode_t mode);
  
  int timeout = 20000;
  String ssid;
  String password;
};