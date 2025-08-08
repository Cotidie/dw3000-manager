#include "dw3000.h"
#include "SPI.h"
#include "DW3000Manager.h"
#include "WiFiManager.h"
#include "NetworkService.h"
#include <ArduinoJson.h>
#include <MemoryCheck.h>

#define TX_ANT_DLY 16385
#define RX_ANT_DLY 16385

/* Python Remote Server Related */
const String host = "141.223.84.133";
const uint16_t port = 20001;

/* WiFi Connectivity */
const String SSID = "AIoT";
const String password = "your password";

/* Utility Objects */
DW3000* dwt;
WiFiManager wifi;
NetworkService service(host, port);

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
  Serial.begin(115200);
  dwt = new DW3000();
  
  // Step 1. Configure UWB DW3000
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

  // // Step 2. Configure WiFi Connectivity
  wifi.begin();
  wifi.connect(SSID, password);
  
  Serial.println("Diagnostics");
  Serial.println("Setup over........");
}

void loop() {
  shared_ptr<Frame> frame = dwt->receiveFrame();
  Serial.println("Frame Received!");

  CIRs& cirs = dwt->extractCIRs();
  Diagnostics& diags = dwt->extractDiagnostics();
  uint8_t dgc = dwt->extractDGC();

  JsonDocument doc;
  doc["CIRs"].set(cirs.toJson());
  doc["Diagnostic"].set(diags.toJson());
  doc["DGC"].set(dgc);
  
  auto response = service.sendJSON(doc);
  Serial.print("Response Code: "); Serial.println(response->getResponseCode());
  Serial.print("Error: "); Serial.println(response->getError());
}
