#include "dw3000.h"
#include "SPI.h"
#include "DW3000Manager.h"
#include <MemoryCheck.h>

#define TX_ANT_DLY 16385
#define RX_ANT_DLY 16385

char cir_start[] = "START OF CIR";
char cir_end[] = "END OF CIR";

DW3000* dwt;

/* Default communication configuration. We use default non-STS DW mode. */
static dwt_config_t config = {
    5,                /* Channel number. */
    DWT_PLEN_128,     /* Preamble length. Used in TX only. */
    DWT_PAC8,         /* Preamble acquisition chunk size. Used in RX only. */
    9,                /* TX preamble code. Used in TX only. */
    9,                /* RX preamble code. Used in RX only. */
    1,                /* 0 to use standard 8 symbol SFD, 1 to use non-standard 8 symbol, 2 for non-standard 16 symbol SFD and 3 for 4z 8 symbol SDF type */
    DWT_BR_6M8,       /* Data rate. */
    DWT_PHRMODE_STD,  /* PHY header mode. */
    DWT_PHRRATE_STD,  /* PHY header rate. */
    (129 + 8 - 8),    /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
    DWT_STS_MODE_OFF, /* STS disabled */
    DWT_STS_LEN_64,   /* STS length see allowed values in Enum dwt_sts_lengths_e */
    DWT_PDOA_M0       /* PDOA mode off */
};

void setup() {
  Serial.begin(19200);
  
  // Step 1. Configure DW3000 Firmware
  DWStatus status = dwt->begin();
  if (status != DWStatus::OK) {
    Serial.print("Init or Idle failed.");
    while (1);
  }
  status = dwt->configure(&config);
  if (status != DWStatus::OK) {
    Serial.print("Configuration failed.");
    while (1);
  }

  dwt->enableLED();
  dwt->setAntennaDelay(RX_ANT_DLY, TX_ANT_DLY);
  dwt->setLNAPAMode(true, true);
  dwt->setDiagnosticsLevel(DiagnosticsLevel::ALL);
}

void loop() {
  shared_ptr<Frame> frame = dwt->receiveFrame();
  Serial.println("Frame Received!");
  Serial.print("Data: ");             Serial.println(frame->getData());
  Serial.print("Sequence Number: ");  Serial.println(frame->getSequenceNumber());
  Serial.print("Src Address: ");      Serial.println(frame->getSrcAddress());
  Serial.print("Dest Address: ");     Serial.println(frame->getDestAddress());
  Serial.print("Total Length: ");     Serial.println(frame->getLength());

  CIRs& cirs = dwt->extractCIRs();
  
  Serial.println(cir_start);
  for (int idx=0; idx < cirs.getLength(); idx++) {
    Serial.print(idx);          Serial.print(",");
    Serial.print(cirs[idx].real);    Serial.print(",");
    Serial.print(cirs[idx].imaginary); Serial.println();
  }
  Serial.println(cir_end);

  printFreeHeap();
  printFreeStack();
}
