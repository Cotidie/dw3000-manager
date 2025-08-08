#include "NetworkService.h"

String ENDPOINT_TEXT = "/text";
String ENDPOINT_JSON = "/json";

shared_ptr<Response> NetworkService::sendText(String data) {
    if (!http.begin(host, port, ENDPOINT_TEXT)) {
        return make_shared<ErrorResponse>("Couldn't connect to host");
    }

    http.addHeader("Content-Type", "text/plain");

    int httpResponseCode = http.POST(data);
    http.end();

    if (httpResponseCode <= 0) {
      return make_shared<ErrorResponse>(http.errorToString(httpResponseCode));
    }

    return make_shared<SuccessResponse>(httpResponseCode);
}

shared_ptr<Response> NetworkService::sendJSON(JsonDocument& doc) {
    if (!http.begin(host, port, ENDPOINT_JSON)) {
        return make_shared<ErrorResponse>("Couldn't connect to host");
    }

    http.addHeader("Content-Type", "application/json");

    String jsonString;
    serializeJson(doc, jsonString);

    int httpResponseCode = http.POST(jsonString);
    http.end();

    if (httpResponseCode <= 0) {
      return make_shared<ErrorResponse>(http.errorToString(httpResponseCode));
    }

    return make_shared<SuccessResponse>(httpResponseCode);
}