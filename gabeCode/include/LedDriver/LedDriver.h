// LED Driver written to follow along with TDDEC.
// Written by Gabriel Rubin (06/03/2025).

#pragma once

#include <cstdint>

class LedDriver
{
    public:
        LedDriver() = delete;
        LedDriver(uint16_t * const address);
        ~LedDriver();

        void turnOn(const uint16_t ledNum);
        void turnOff(const uint16_t ledNum);

    private:
    uint16_t * const _ledsAddress = nullptr;
};
