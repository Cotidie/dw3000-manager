#pragma once

#include <Arduino.h>
#include <string>

class Serializable {
public:
    virtual void toJSON(Json) = 0;
    virtual String fromJSON() = 0;
};