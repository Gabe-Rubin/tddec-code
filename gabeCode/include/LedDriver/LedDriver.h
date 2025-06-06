#ifndef D_LedDriver_H
#define D_LedDriver_H

// LED Driver written to follow along with TDDEC.
// Written by Gabriel Rubin (06/03/2025).

#include <cstdint>

class LedDriver
{
    public:
        LedDriver() = delete;
        LedDriver(uint16_t * const address);
        ~LedDriver();

        void turnOn(const int ledNum);
        void turnOff(const int ledNum);

        void turnAllOn();
        void turnAllOff();
        
        bool isOn(const int ledNum);
        bool isOff(const int ledNum);

    private:
        void updateHardware();

        uint16_t * const _ledsAddress = nullptr;
        uint16_t _ledsImage = 0;
};

#endif // D_LedDriver_H
