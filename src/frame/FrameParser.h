#pragma once

#include <Arduino.h>
#include <memory>
#include "dw3000.h"
#include "CustomFrame.h"

#define FRAME_TYPE_BIT_MASK 0b111

class FrameParser {
public:
    FrameParser() {};

    shared_ptr<Frame> parseRXBuffer();
    shared_ptr<Frame> parse(const uint8_t* buffer, uint8_t len);

private:
    FrameType parseType(const uint8_t* buffer);
};