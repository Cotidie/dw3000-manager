#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include "stdint.h"
#include "interface/Serializable.h"

/**
 * @brief Represents a single Channel Impulse Response (CIR) sample.
 * 
 * Each sample contains a real and imaginary component, derived from
 * 24-bit signed values extracted from the DW3000 accumulator.
 */
class CIR {
public:
    CIR() {} ;
    CIR(int32_t real, int32_t imaginary) {
        this->real = real;
        this->imaginary = imaginary;
    }

    // JSON format: [real, imaginary]
    JsonDocument toJson() {
        JsonDocument arr;
        arr.add(real);
        arr.add(imaginary);

        return arr;
    }

    int32_t real = 0;
    int32_t imaginary = 0;
};

class CIRs : public Serializable {
public:
    CIRs(uint16_t len) {
        this->cirs = new CIR[len];
        this->len = len;
    }

    ~CIRs() { delete[] this->cirs; }

    CIR& operator[](int idx) { return cirs[idx]; }

    uint16_t getLength() { return this->len; }

    // JSON Foramt: [ [re, img], [re, img], ... ]
    JsonDocument toJson() {
        JsonDocument arrCIRs;
        for (int i=0; i<len; i++) {
            JsonDocument arrCIR = cirs[i].toJson();
            arrCIRs.add(arrCIR);
            arrCIR.clear();
        }

        return arrCIRs;
    }

private:
    CIR* cirs;
    uint16_t len;
};

