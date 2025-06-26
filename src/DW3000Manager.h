#pragma once

#include <Arduino.h>
#include <memory>
#include "stdint.h"
#include "dw3000.h"
#include "entity/CIR.h"
#include "frame/Frame.h"
#include "frame/FrameParser.h"
#include "frame/FrameBuilder.h"

using namespace std;


/**
 * @brief Status codes for DW3000 operation. 
 * This follows the operational states in 2.4.1 State diagram of DW3000 User Manual.
 */
enum class DWStatus {
    OK,             // Everything OK
    NOT_IDLE,       // Device not in IDLE_RC state
    INIT_FAILED,    // Initialization failed
    CONFIG_FAILED   // Configuration failed
};

/**
 * @brief DW3000 interface class that wraps dw3000.h library. Responsible for TX, RX, and hardware control.
 */
class DW3000 {
public:
    DW3000();
    ~DW3000();

    /**
     * @brief Initializes the DW3000 and checks whether it reaches the IDLE_RC state.
     * 
     * This method should be called before any other operations.
     * It includes a delay or SPI_RDY check to ensure the device is ready.
     * 
     * @return DWTStatus::OK if successful
    */
    DWStatus begin();

    /**
     * @brief Configures the DW3000 with the provided configuration parameters.
     * 
     * @param config Pointer to a valid `dwt_config_t` configuration structure.
     * @return DWTStatus::OK if successful, or DWTStatus::ConfigFailed on failure.
    */
    DWStatus configure(dwt_config_t *config);

    /**
     * @brief Enables the onboard diagnostic LEDs on the DW3000. (D1 Port)
     * 
     * Primarily used for debugging and visibility of TX/RX activity.
    */
    void enableLED();

    /**
     * @brief Sets the RX and TX antenna delays used for time-of-flight and timestamp correction.
     * 
     * @param rx RX antenna delay in device time units.
     * @param tx TX antenna delay in device time units.
    */
    void setAntennaDelay(uint16_t rx, uint16_t tx);

    /**
     * @brief Enables the LNA (Low Noise Amplifier) and PA (Power Amplifier).
     * 
     * Typically disabled for low-power applications.
     * 
     * @param lna true to enable LNA, false to disable.
     * @param pa true to enable PA, false to disable.
    */
    void setLNAPAMode(bool lna, bool pa);

    /** @brief A blocking call that waits for a UWB frame. */
    shared_ptr<Frame> receiveFrame();

    /** @brief A blocking call that sends a UWB frame in TXBuffer. */
    void transmitFrame(shared_ptr<Frame> frame);

    /**
     * @brief Extracts CIR (Channel Impulse Response) samples from the DW3000 accumulator.
     *
     * This method reads the full CIR buffer from the DW3000 and converts it into an array of complex samples.
     * 
     * @return CIRFrame containing a pointer to CIR data and the number of samples.
    */
    CIRs& extractCIR();
private:
    DWStatus status = DWStatus::OK;

    // ⚠️ WARNING: These buffers MUST be allocated on the heap (not stack) 
    // to avoid overflow on Arduino boards like ESP32.
    // Note that ESP32 only allocates 8KB to stack memory, while ~180KB to static, heap area.
    uint8_t *cirBuffer;
    CIRs* cirs;
};