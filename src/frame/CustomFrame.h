#pragma once

#include <stdint.h>
#include <string>
#include "Frame.h"

using namespace std;

#define CUSTOM_FRAME_HEADER_SIZE 19
#define FRAME_CHECK_SEQUENCE_SIZE 2

/**
 * @brief A UWB frame with a custom-made header and a string payload.
 * 
 * Frame layout (custom-defined):
 * - Fixed-size header (19 bytes total):
 *   - Sequence Number (2 bytes)
 *   - Destination Address (8 bytes)
 *   - Source Address (8 bytes)
 * - Variable-length payload (`String` data)
 * - Reserved tail (2 bytes) for frame check sequence (FCS)
 * 
 * @note This frame format is not standard and should be parsed or constructed accordingly.
 * 
 */
class CustomFrame : public Frame {
public:
    CustomFrame(uint16_t len);
    CustomFrame(const uint8_t *frame, uint16_t len);

    void setSequenceNumber(uint8_t num);
    void setDestAddress(uint64_t addr);
    void setSrcAddress(uint64_t addr);
    void setData(String data);

    uint8_t getSequenceNumber();
    uint64_t getDestAddress();
    uint64_t getSrcAddress();
    String getData();
};