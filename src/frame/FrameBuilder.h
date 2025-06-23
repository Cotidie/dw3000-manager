#pragma once

#include <Arduino.h>
#include <string>
#include <memory>
#include "Frame.h"

using namespace std;

#define FRAME_CHECK_SEQUENCE_SIZE 2

/**
 * @brief Builder class for constructing UWB Frame objects.
 * 
 * FrameBuilder simplifies the creation of different frame types (e.g., CustomFrame)
 * by allowing clients to specify common fields like sequence number, source/destination
 * addresses, and payload data through chained setter methods. Once all parameters are set,
 * call the `build()` method to return a fully constructed `Frame` instance.
 * 
 * Supported frame types and their size computations are handled internally, including 
 * header size and optional fields like checksum space.
 * 
 * Usage:
 * @code
 * auto frame = FrameBuilder(FrameType::Custom)
 *                 .setSequenceNumber(1)
 *                 .setSrcAddress(0x1234)
 *                 .setDestAddress(0x5678)
 *                 .setData("Hello")
 *                 .build();
 * @endcode
 */
class FrameBuilder {
public:
    FrameBuilder(FrameType type) {this->type = type;}
    
    FrameBuilder& setSequenceNumber(uint8_t num);
    FrameBuilder& setDestAddress(uint64_t addr);
    FrameBuilder& setSrcAddress(uint64_t addr);
    FrameBuilder& setData(String data);

    shared_ptr<Frame> build();

private:
    /**
     * @brief Calculates the total byte length of the frame based on its type.
     * 
     * @param type The type of frame to calculate length for.
     * @return The total length in bytes required to allocate the frame buffer.
     * 
     */
    uint16_t calculateLength(FrameType type);

    FrameType type;
    uint8_t seqNum = 0;
    uint64_t addrDest = 0;
    uint64_t addrSrc = 0;
    String data;
};