#pragma once

#include <Arduino.h>
#include <memory>
#include <ArduinoJson.h>
#include "HTTPClient.h"
#include "Response.h"

using namespace std;

class NetworkService {
public:
  NetworkService(String host, uint16_t port) {
    this->host = host;
    this->port = port;
  };

  shared_ptr<Response> sendText(String data);
  shared_ptr<Response> sendJSON(JsonDocument& doc);

private:
  HTTPClient http;
  String host;
  uint16_t port;
};