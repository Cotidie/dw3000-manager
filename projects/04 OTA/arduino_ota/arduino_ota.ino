#include <WiFi.h>        // For connecting ESP32 to WiFi
#include <ArduinoOTA.h>  // For enabling over-the-air updates

const char* ssid = "AIoT";  // Change to your WiFi Network name
const char* password = "monetghgh";  // Change to your password

void setup() {
  Serial.begin(19200);
  WiFi.begin(ssid, password);  // Connect to WiFi - defaults to WiFi Station mode

  // Ensure WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  ArduinoOTA.begin();  // Starts OTA
}

void loop() {

  ArduinoOTA.handle();  // Handles a code update request
  Serial.println("Hello OTA");
  delay(3000);
  // All loop you're code goes here.
}