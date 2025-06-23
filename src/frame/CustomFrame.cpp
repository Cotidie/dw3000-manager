#include "CustomFrame.h"

#define SEQUENCE_NUMBER_IDX 2
#define SEQUENCE_NUMBER_SIZE 1
#define DEST_ADDRESS_IDX 3
#define DEST_ADDRESS_SIZE 8
#define SRC_ADDRESS_IDX 11
#define SRC_ADDRESS_SIZE 8
#define DATA_IDX 19

using namespace std;

CustomFrame::CustomFrame(uint16_t len) {
    this->buffer = new uint8_t[len]();
    this->len = len;

    this->setFrameType(FrameType::Custom);
}

CustomFrame::CustomFrame(const uint8_t *frame, uint16_t len) {
    this->buffer = new uint8_t[len]();
    memcpy(this->buffer, frame, len);
    this->len = len;

    void setFrameType(FrameType type);
}

void CustomFrame::setSequenceNumber(uint8_t num) {
    memcpy(&(this->buffer[SEQUENCE_NUMBER_IDX]), &num, SEQUENCE_NUMBER_SIZE);
}

void CustomFrame::setDestAddress(uint64_t addr) {
    memcpy(&(this->buffer[DEST_ADDRESS_IDX]), &addr, DEST_ADDRESS_SIZE);
}

void CustomFrame::setSrcAddress(uint64_t addr) {
    memcpy(&(this->buffer[SRC_ADDRESS_IDX]), &addr, SRC_ADDRESS_SIZE);
}

void CustomFrame::setData(String data) {
    memcpy(&(this->buffer[DATA_IDX]), data.c_str(), data.length());
}

uint8_t CustomFrame::getSequenceNumber() {
    uint8_t seqNum;
    memcpy(&seqNum, &(this->buffer[SEQUENCE_NUMBER_IDX]), SEQUENCE_NUMBER_SIZE);
    return seqNum;
}

uint64_t CustomFrame::getDestAddress() {
    uint64_t addr;
    memcpy(&addr, &(this->buffer[DEST_ADDRESS_IDX]), DEST_ADDRESS_SIZE);
    return addr;
}

uint64_t CustomFrame::getSrcAddress() {
    uint64_t addr;
    memcpy(&addr, &(this->buffer[SRC_ADDRESS_IDX]), SRC_ADDRESS_SIZE);
    return addr;
}

String CustomFrame::getData() {
    uint16_t dataLength = this->len - CUSTOM_FRAME_HEADER_SIZE - FRAME_CHECK_SEQUENCE_SIZE;
    char* data = new char[dataLength];
    memcpy(data, &(this->buffer[DATA_IDX]), dataLength);
    String str = String(data, dataLength);
    delete[] data;
    return str;
}