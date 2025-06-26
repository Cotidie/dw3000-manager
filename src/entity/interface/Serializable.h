#pragma once

#include <ArduinoJson.h>

/**
 * @brief Abstract interface for JSON serializable classes using ArduinoJson.
 *
 * @note The caller is responsible for managing (freeing) the returned JsonDocument's memory.
 * 
*/
class Serializable {
public:

    /**
     * @brief Serializes the class instance into a JsonDocument.
     *
     * @return A dynamically allocated JsonDocument containing the serialized representation.
     * @warning The returned JsonDocument must be freed by the caller after use.
     * 
    */
    virtual JsonDocument toJson() = 0;
};