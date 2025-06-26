#pragma once

#include <Arduino.h>
#include <ArduinoJson>
#include "stdint.h"

class CIRs {
public:
    CIRs(uint16_t len) {
        this->cirs = new CIR[len];
        this->len = len;
    }

    ~CIRs() { delete[] this->cirs; }

    CIR& operator[](int idx) { return cirs[idx]; }

    void toJson(JsonArray cirsJson) {
        for (int i=0; i<len; i++) {
            JsonArray cirJson = cirsJson.add<JsonArray>();
            this->cirs[i].toJson(cirJson);
        }
    }

private:
    CIR* cirs;
    uint16_t len;
};

/**
 * @brief Represents a single Channel Impulse Response (CIR) sample.
 * 
 * Each sample contains a real and imaginary component, derived from
 * 24-bit signed values extracted from the DW3000 accumulator.
 */
class CIR {
public:
    CIR(int32_t real, int32_t imaginary) {
        this->real = real;
        this->imaginary = imaginary;
    }

    void toJson(JsonArray json) {
        json.add(real);
        json.add(imaginary);
    }

    int32_t real;
    int32_t imaginary;
};