#pragma once

#include "Arduino.h"
#include "stdint.h"
#include <string>

using namespace std;

enum class FrameType : uint8_t {
    Custom = 0b110,
    NONE = 0b1000,
};

FrameType bitsToFrameType(uint8_t bits);

/**
 * @brief Abstract base class representing a generic UWB frame structure.
 * 
 * This class defines a common interface for all UWB frame types, such as CustomFrame.
 * It is not meant to be instantiated directly. Instead, derived classes must implement
 * all pure virtual methods to define the specific layout and behavior of different frame types.
 * 
 * @note Use derived classes to construct and manipulate actual frame instances.
 */
class Frame {
public:
    ~Frame() {delete[] this->buffer;}

    virtual void setSequenceNumber(uint8_t num) = 0;
    virtual void setDestAddress(uint64_t addr) = 0;
    virtual void setSrcAddress(uint64_t addr) = 0;
    virtual void setData(String data) = 0;


    virtual uint8_t getSequenceNumber() = 0;
    virtual uint64_t getDestAddress() = 0;
    virtual uint64_t getSrcAddress() = 0;
    virtual String getData() = 0;

    uint16_t getFrameControl();
    FrameType getFrameType();
    uint32_t getLength() { return this->len; }
    uint8_t* getBuffer() const { return this->buffer; }

protected:
    void setFrameType(FrameType type);

    FrameType type;
    uint8_t *buffer;
    uint16_t len = 0;
};
