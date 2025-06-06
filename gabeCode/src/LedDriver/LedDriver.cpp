#include "LedDriver.h"
extern "C"
{
#include "RuntimeError.h"
}
#include <cstdint>

// Some Enums to hide magic numbers and improve readability.

enum {
    ALL_LEDS_ON = 0xffff,
    ALL_LEDS_OFF = 0x0000
};

enum {
    FIRST_LED = 1,
    LAST_LED = 16
};

namespace // LedDriverHelpers
{
    inline const uint16_t convertLedNumberToBitPosition(const int ledNum)
    {
        return (1 << (ledNum - 1));
    }

    bool isLedInBounds(const int ledNum)
    {
        bool isInBounds = false;
        if(ledNum >= FIRST_LED && ledNum <= LAST_LED)
        {
            isInBounds = true;
        }
        else
        {
            RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNum);
        }
        return isInBounds;
    }

    void setLedImageBit(const int ledNum, uint16_t &image)
    {
        image |= convertLedNumberToBitPosition(ledNum);
    }

    void clearLedImageBit(const int ledNum, uint16_t &image)
    {
        image &= ~convertLedNumberToBitPosition(ledNum);
    }
}

LedDriver::LedDriver(uint16_t * const address) : _ledsAddress(address)
{
    this->_ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

LedDriver::~LedDriver()
{
}

void LedDriver::turnOn(const int ledNum)
{
    if(isLedInBounds(ledNum))
    {
        setLedImageBit(ledNum, this->_ledsImage);
        updateHardware();
    }
}

void LedDriver::turnOff(const int ledNum)
{
    if(isLedInBounds(ledNum))
    {
        clearLedImageBit(ledNum, this->_ledsImage);
        updateHardware();
    }
}

void LedDriver::turnAllOn()
{
    this->_ledsImage = ALL_LEDS_ON;
    updateHardware();
}

void LedDriver::turnAllOff()
{
    this->_ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver::updateHardware()
{
    *(this->_ledsAddress) = this->_ledsImage;
}

bool LedDriver::isOn(const int ledNum)
{
    bool on = false;
    if (isLedInBounds(ledNum))
    {
        on = this->_ledsImage & convertLedNumberToBitPosition(ledNum);
    }
    return on;
}

bool LedDriver::isOff(const int ledNum)
{
    return !this->isOn(ledNum);
}
