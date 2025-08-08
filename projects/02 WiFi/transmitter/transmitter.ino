#include "WiFiManager.h"
#include "HTTPClient.h"

WiFiManager wifi;
HTTPClient http;

const String host = "141.223.84.133";
const int port = 20001;

String getInput(String msg = "") {
  Serial.println(msg);
  while (Serial.available() == 0) {}
  String input = Serial.readString();
  input.trim();
  return input;
}

void setup() {
  Serial.begin(19200);
  
  wifi.scan();

  String ssid = getInput("Enter SSID: ");
  String password = getInput("Enter Password: ");
  wifi.connect(ssid, password);

  if (!http.begin(host, port, "/message")) {
    Serial.println("Couldn't connect to host");
    while (1);
  }
  http.addHeader("Content-Type", "text/plain");
}

void loop() {
  int httpResponseCode = http.POST("Hello There!");
  if (httpResponseCode > 0) {
      Serial.printf("POST success: %d\n", httpResponseCode);
    } else {
      Serial.printf("POST failed: %s\n", http.errorToString(httpResponseCode).c_str());
    }
  delay(3000);
}
