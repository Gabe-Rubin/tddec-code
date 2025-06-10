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
    LAST_LED = 1,
    FIRST_LED = 16
};

namespace // LedDriverHelpers
{
    inline const uint16_t convertLedNumberToBitPosition(const int ledNum)
    {
        return (0x8000 >> (ledNum - 1));
    }

    bool isLedInBounds(const int ledNum)
    {
        bool isInBounds = false;
        if(ledNum >= LAST_LED && ledNum <= FIRST_LED)
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

    void invertBits(uint16_t &image)
    {
        image = (uint16_t)(~image);
    }
}

LedDriver::LedDriver(uint16_t * const address, bool invertedLogic) : _ledsAddress(address), _invertedLogic{invertedLogic}
{
    this->turnAllOff();
    updateHardware();
}

LedDriver::~LedDriver()
{
}

void LedDriver::turnOn(const int ledNum)
{
    if(isLedInBounds(ledNum))
    {
        if(this->_invertedLogic)
        {
            clearLedImageBit(ledNum, this->_ledsImage);
        }
        else
        {
            setLedImageBit(ledNum, this->_ledsImage);
        }
        updateHardware();
    }
}

void LedDriver::turnOff(const int ledNum)
{
    if(isLedInBounds(ledNum))
    {
        if(this->_invertedLogic)
        {
            setLedImageBit(ledNum, this->_ledsImage);
        }
        else
        {
            clearLedImageBit(ledNum, this->_ledsImage);
        }
        updateHardware();
    }
}

void LedDriver::turnAllOn()
{
    this->_ledsImage = ALL_LEDS_ON;
    if(this->_invertedLogic)
    {
        invertBits(this->_ledsImage);
    }
    updateHardware();
}

void LedDriver::turnAllOff()
{
    this->_ledsImage = ALL_LEDS_OFF;
    if(this->_invertedLogic)
    {
        invertBits(this->_ledsImage);
    }
    updateHardware();
}

void LedDriver::updateHardware()
{
    *(this->_ledsAddress) = this->_ledsImage;
}

bool LedDriver::isOn(const int ledNum) const
{
    bool on = false;
    if(isLedInBounds(ledNum))
    {
        on = this->_ledsImage & convertLedNumberToBitPosition(ledNum);
        if(this->_invertedLogic)
        {
            on = !on;
        }
    }
    return on;
}

bool LedDriver::isOff(const int ledNum) const
{
    return !this->isOn(ledNum);
}

bool LedDriver::isLogicInverted() const
{
    return this->_invertedLogic;
}

void LedDriver::setLogicInverted(const bool inverted)
{
    this->_invertedLogic = inverted;
    this->_ledsImage = ~this->_ledsImage;
    this->updateHardware();
}
