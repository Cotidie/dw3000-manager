# Over The Air Updates
Easily update a Makerfabs ESP32 UWB DW3000 device wirelessly using ArduinoOTA.

## ✅ Prerequisites
- 1x ESP32 UWB DW3000 Device (Makerfab)
- Arduino IDE with required libraries:
  - `ArduinoJson`
  - `HTTPClient`
  - `ArduinoOTA`
- Same WiFi Network

## 🚀 Setup & Run
Ensure the computer and ESP32 device are connected to the same Wi-Fi network. Once OTA code is uploaded, the Arduino IDE will detect the ESP32 as a wireless port.

1. Add Minimal OTA Code to the Sketch
  ```cpp
  #include <WiFi.h>        // For connecting ESP32 to WiFi
  #include <ArduinoOTA.h>  // For enabling over-the-air updates

  const char* ssid = "453-454";  // Change to your WiFi Network name
  const char* password = "453453453";  // Change to your password

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
  }
  ```

  2. Flash the Device via USB
    - for the first time only
  
  3. Select the Network Port in ArduinoIDE
    ![network port](../../.images/README.png)  

## 🖼️ Screenshot

## Reference
- [ElegantOTA - ESP32 OTA Updates](https://randomnerdtutorials.com/esp32-ota-elegantota-arduino/)
- [ArduinoOTA Tutorial](https://www.programmingelectronics.com/arduinoota/)