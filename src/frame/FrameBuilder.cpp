#include "FrameBuilder.h"
#include "CustomFrame.h"

FrameBuilder& FrameBuilder::setSequenceNumber(uint8_t num) {
    this->seqNum = num;
    return *this;
}

FrameBuilder& FrameBuilder::setDestAddress(uint64_t addr) { 
    this->addrDest = addr; 
    return *this;
} 

FrameBuilder& FrameBuilder::setSrcAddress(uint64_t addr) { 
    this->addrSrc = addr; 
    return *this;
}

FrameBuilder& FrameBuilder::setData(String data) { 
    this->data = data;
    return *this;
}

shared_ptr<Frame> FrameBuilder::build() {
    uint16_t frameLength = calculateLength(type);

    if (type == FrameType::Custom) {
        auto frame = make_shared<CustomFrame>(frameLength);
        frame->setSequenceNumber(seqNum);
        frame->setDestAddress(addrDest);
        frame->setSrcAddress(addrSrc);
        frame->setData(data);
        return frame;
    }

    return nullptr;
}

uint16_t FrameBuilder::calculateLength(FrameType type) {
    if (type == FrameType::Custom) {
        return CUSTOM_FRAME_HEADER_SIZE + data.length() + FRAME_CHECK_SEQUENCE_SIZE;
    }

    return 0;
}