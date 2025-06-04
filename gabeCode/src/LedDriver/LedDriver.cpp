#include "LedDriver.h"
#include <cstdint>

LedDriver::LedDriver(uint16_t * const address) : _ledsAddress(address)
{
    *(this->_ledsAddress) = 0x0000;
}

LedDriver::~LedDriver()
{
}

void LedDriver::turnOn(const uint16_t ledNum)
{
    *(this->_ledsAddress) = 1;
    return;
}

void LedDriver::turnOff(const uint16_t ledNum)
{
    *(this->_ledsAddress) = 0;
}
