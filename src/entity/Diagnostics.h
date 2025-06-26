#pragma once

#include "dw3000.h"
#include "interface/Serializable.h"

class Diagnostics : public Serializable {
public:
    Diagnostics() {};

    JsonDocument toJson() {
        JsonDocument doc;

        JsonArray ipatovRxTime = doc["ipatovRxTime"].to<JsonArray>();
        for (int i=0; i<sizeof(diags.ipatovRxTime); i++) {
            ipatovRxTime.add(diags.ipatovRxTime[i]);
        }
        doc["ipatovRxStatus"] = diags.ipatovRxStatus;
        doc["ipatovPOA"] = diags.ipatovPOA;

        JsonArray stsRxTime = doc["stsRxTime"].to<JsonArray>();
        for (int i=0; i<sizeof(diags.stsRxTime); i++) {
            stsRxTime.add(diags.stsRxTime[i]);
        }
        doc["stsRxStatus"] = diags.stsRxStatus;
        doc["stsPOA"] = diags.stsPOA;


        JsonArray sts2RxTime = doc["sts2RxTime"].to<JsonArray>();
        for (int i=0; i<sizeof(diags.sts2RxTime); i++) {
            sts2RxTime.add(diags.sts2RxTime[i]);
        }
        doc["sts2RxStatus"] = diags.sts2RxStatus;
        doc["sts2POA"] = diags.sts2POA;
        
        JsonArray tdoa = doc["tdoa"].to<JsonArray>();
        for (int i=0; i<sizeof(diags.tdoa); i++) {
            tdoa.add(diags.tdoa[i]);
        }
        doc["pdoa"] = diags.pdoa;
        
        doc["xtalOffset"] = diags.xtalOffset;
        doc["ciaDiag1"] = diags.ciaDiag1;

        doc["ipatovPeak"] = diags.ipatovPeak;
        doc["ipatovPower"] = diags.ipatovPower;
        doc["ipatovF1"] = diags.ipatovF1;
        doc["ipatovF2"] = diags.ipatovF2;
        doc["ipatovF3"] = diags.ipatovF3;
        doc["ipatovFpIndex"] = diags.ipatovFpIndex;
        doc["ipatovAccumCount"] = diags.ipatovAccumCount;

        doc["stsPeak"] = diags.stsPeak;
        doc["stsPower"] = diags.stsPower;
        doc["stsF1"] = diags.stsF1;
        doc["stsF2"] = diags.stsF2;
        doc["stsF3"] = diags.stsF3;
        doc["stsFpIndex"] = diags.stsFpIndex;
        doc["stsAccumCount"] = diags.stsAccumCount;

        doc["sts2Peak"] = diags.sts2Peak;
        doc["sts2Power"] = diags.sts2Power;
        doc["sts2F1"] = diags.sts2F1;
        doc["sts2F2"] = diags.sts2F2;
        doc["sts2F3"] = diags.sts2F3;
        doc["sts2FpIndex"] = diags.sts2FpIndex;
        doc["sts2AccumCount"] = diags.sts2AccumCount;

        return doc;
    }

    dwt_rxdiag_t diags;
};