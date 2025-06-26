#include "dw3000.h"
#include "SPI.h"
#include "DW3000Manager.h"

#define PIN_RST 27
#define PIN_IRQ 34
#define PIN_SS 4

#define RX_BUFFER_SIZE 127

#define CIR_SAMPLES 1016
#define CIR_BYTES_PER_SAMPLE 6
#define CIR_BUFFER_SIZE (CIR_SAMPLES * CIR_BYTES_PER_SAMPLE + 1)

using namespace std;

extern SPISettings _fastSPI;
extern dwt_txconfig_t txconfig_options;

DW3000::DW3000() {}

DW3000::~DW3000() {
    delete[] this->cirBuffer;
    delete[] this->cirs;
}

DWStatus DW3000::begin() {
    this->cirBuffer = new uint8_t[CIR_BUFFER_SIZE];
    this->cirs = new CIRs(CIR_SAMPLES);

    // SPI Configuration -> $2.3.1.1 SPI Operating Modes
    // onyl clock speed is configurable, others are mandatory by manual
    // - clock speed: 16 MHz
    // - Bit Order: MSB on transmission
    // - SPI Mode: 0 (idle on Low, read at rising edge)
    _fastSPI = SPISettings(16000000L, MSBFIRST, SPI_MODE0);
    spiBegin(PIN_IRQ, PIN_RST);
    spiSelect(PIN_SS);

    // Time needed for DW3000 to start up (transition from INIT_RC to IDLE_RC, or could wait for SPIRDY event)
    // ref. 5.1.15 dwt_checkidlerc()
    delay(2); 
    if (!dwt_checkidlerc()) 
        return DWStatus::NOT_IDLE;

    if (dwt_initialise(DWT_DW_INIT) == DWT_ERROR)
        return DWStatus::INIT_FAILED;

    return DWStatus::OK;
}

DWStatus DW3000::configure(dwt_config_t *config) {
    // if the dwt_configure returns DWT_ERROR either the PLL or RX calibration has failed the host should reset the device
    if (dwt_configure(config)) {
        return DWStatus::CONFIG_FAILED;
    }

    /* Configure the TX spectrum parameters (power, PG delay and PG count) */
    dwt_configuretxrf(&txconfig_options);
    return DWStatus::OK;
}

void DW3000::enableLED() {
    dwt_setleds(DWT_LEDS_ENABLE | DWT_LEDS_INIT_BLINK);
}

void DW3000::setAntennaDelay(uint16_t rx, uint16_t tx) {
    dwt_setrxantennadelay(rx);
    dwt_settxantennadelay(tx);
}

void DW3000::setLNAPAMode(bool lna, bool pa) {
    uint8_t bits = 0;
    if (lna) bits |= DWT_LNA_ENABLE;
    if (pa) bits |= DWT_PA_ENABLE;

    dwt_setlnapamode(bits);
}

shared_ptr<Frame> DW3000::receiveFrame() {
    // Immediately enable RX
    dwt_rxenable(DWT_START_RX_IMMEDIATE);

    while (true) {
        uint32_t status_reg = dwt_read32bitreg(SYS_STATUS_ID);
        uint32_t is_received = status_reg & SYS_STATUS_RXFCG_BIT_MASK;
        if (is_received) break;
    }

    dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_GOOD);

    return FrameParser().parseRXBuffer();
}

void DW3000::transmitFrame(shared_ptr<Frame> frame) {
    dwt_writetxdata(frame->getLength(), frame->getBuffer(), 0);
    dwt_writetxfctrl(frame->getLength(), 0, 0);

    dwt_starttx(DWT_START_TX_IMMEDIATE);
}

CIRs& DW3000::extractCIR() {
    dwt_readaccdata(this->cirBuffer, CIR_BUFFER_SIZE, 0);
    for (int idx = 0; idx < CIR_SAMPLES; idx++) {
        int i = 1 + idx*CIR_BYTES_PER_SAMPLE;

        // Extract real part (24-bit signed)
        (*cirs)[idx].real = ((int32_t)(int8_t) this->cirBuffer[i + 2] << 16) +
                ((int32_t) this->cirBuffer[i + 1] << 8) +
                (int32_t) this->cirBuffer[i];

        // Extract imag part (24-bit signed)
        (*cirs)[idx].imaginary = ((int32_t)(int8_t) this->cirBuffer[i + 5] << 16) +
                ((int32_t) this->cirBuffer[i + 4] << 8) +
                (int32_t) this->cirBuffer[i + 3];
    }

    return *cirs;
}