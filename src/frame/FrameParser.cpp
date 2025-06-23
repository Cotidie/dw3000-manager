#include "FrameParser.h"

shared_ptr<Frame> FrameParser::parse(const uint8_t* buffer, uint8_t len) {
    FrameType type = parseType(buffer);

    if (type == FrameType::Custom) {
        return make_shared<CustomFrame>(buffer, len);
    }

    return nullptr;
}

shared_ptr<Frame> FrameParser::parseRXBuffer() {
    uint16_t len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_BIT_MASK;
    uint8_t* buffer = new uint8_t[len];
    dwt_readrxdata(buffer, len, 0);

    auto frame = this->parse(buffer, len);
    
    delete[] buffer;
    return frame;
}

FrameType FrameParser::parseType(const uint8_t* buffer) {
    uint16_t frameControl = 0;
    memcpy(&frameControl, buffer, 2);
    uint8_t frameTypeBits = frameControl & FRAME_TYPE_BIT_MASK;
    
    switch (frameTypeBits) {
        case (uint8_t)FrameType::Custom:
            return FrameType::Custom;
        default:
            Serial.println("Not Found");
    }

    
    return FrameType::Custom;
}