#include "WiFiManager.h"

WiFiManager::WiFiManager() {}

void WiFiManager::setTimeout(int millis) { this->timeout = millis; }

int WiFiManager::scan() {
  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("no networks found");
    return n;
  } 
  Serial.print(n);
  Serial.println(" networks found");
  Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
  for (int i = 0; i < n; ++i) {
    // Print SSID and RSSI for each network found
    Serial.printf("%2d", i);                           Serial.print(" | ");
    Serial.printf("%-32.32s", WiFi.SSID(i).c_str()); Serial.print(" | ");
    Serial.printf("%4ld", WiFi.RSSI(i));             Serial.print(" | ");
    Serial.printf("%2ld", WiFi.channel(i));          Serial.print(" | ");
    Serial.println(getWiFiAuthMode(WiFi.encryptionType(i)));
    delay(10);
  }

  return n;
}

wl_status_t WiFiManager::reconnect() {
  return connect(this->ssid, this->password);
}

wl_status_t WiFiManager::connectInteractively() {
  if (scan() == 0) {
    return WL_NO_SSID_AVAIL;
  }
  String ssid = getInput("Enter SSID: ");
  String password = getInput("Enter Password: ");
  return connect(ssid, password);
}

wl_status_t WiFiManager::connectByIndex(int idx, String password) {
  return connect(WiFi.SSID(idx), password);
}

wl_status_t WiFiManager::connect(String ssid, String password) {
  WiFi.begin(ssid, password);
  Serial.println(ssid);
  Serial.println(password);

  int checkInterval = 500;
  int delayedTime = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(checkInterval);
    delayedTime += checkInterval;
    Serial.print(".");

    if (delayedTime > this->timeout) {
      return WL_CONNECT_FAILED;
    }
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  this->ssid = ssid;
  this->password = password;

  return WL_CONNECTED;
}

wl_status_t WiFiManager::getStatus() { return WiFi.status(); }

String WiFiManager::getIPAddress() {
  return WiFi.localIP().toString();
}

String WiFiManager::getInput(String msg) {
  Serial.println(msg);
  while (Serial.available() == 0) {}
  String input = Serial.readString();
  input.trim();
  return input;
}

String WiFiManager::getWiFiAuthMode(wifi_auth_mode_t mode) {
  switch (mode) {
    case WIFI_AUTH_OPEN:            return "open";
    case WIFI_AUTH_WEP:             return "WEP";
    case WIFI_AUTH_WPA_PSK:         return "WPA";
    case WIFI_AUTH_WPA2_PSK:        return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK:    return "WPA+WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-EAP";
    case WIFI_AUTH_WPA3_PSK:        return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK:   return "WPA2+WPA3";
    case WIFI_AUTH_WAPI_PSK:        return "WAPI";
    default:                        return "unknown";
  }
}