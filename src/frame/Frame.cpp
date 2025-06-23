#include "Frame.h"

FrameType bitsToFrameType(uint8_t bits) {
    switch (bits) {
        case 0b110:
            return FrameType::Custom;
    }

    return FrameType::NONE;
};

uint16_t Frame::getFrameControl() {
    uint16_t bits = 0;
    memcpy(&bits, buffer, 2);

    return bits;
}

FrameType Frame::getFrameType() {
    uint16_t bits = 0;
    memcpy(&bits, buffer, 2);

    return bitsToFrameType(bits);
}

void Frame::setFrameType(FrameType type) {
    uint16_t bitsFrameControl = getFrameControl();

    bitsFrameControl &= 0x000;
    bitsFrameControl |= (uint8_t) type;

    memcpy(buffer, &bitsFrameControl, 2);
}