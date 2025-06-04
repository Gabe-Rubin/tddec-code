// Written by Gabe Rubin 06/02/2025 following along with TDD.

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LedDriver.h"
#include "RuntimeErrorStub.h"
}

TEST_GROUP(LedDriver)
{
    uint16_t virtualLeds; // Intentionally not initializing this
                          // since we don't know what the value will be
                          // in the hardware register.
    LedDriver *ledDriver0 = nullptr;

    void setup()
    {
        ledDriver0 = new LedDriver(&virtualLeds);
    }

    void teardown()
    {
        delete ledDriver0;
    }

};

TEST(LedDriver, LedsOffAfterCreate)
{
    uint16_t virtualLeds = 0xffff;
    LedDriver ledDriver0(&virtualLeds);
    LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
    ledDriver0->turnOn(0x0001);
    LONGS_EQUAL(0x0001, virtualLeds);
}

// TEST(LedDriver, TurnOnLedTwo)
// {
//     ledDriver0->turnOn(0x0002);
//     LONGS_EQUAL(0x0002, virtualLeds);
// }

TEST(LedDriver, TurnOffLedOne)
{
    ledDriver0->turnOn(0x0001);
    ledDriver0->turnOff(0x0001);
    LONGS_EQUAL(0x0000, virtualLeds);
}

// TEST(LedDriver, TurnOffLedTwo)
// {
//     ledDriver0->turnOn(0x0002);
//     ledDriver0->turnOff(0x0002);
//     LONGS_EQUAL(0x0000, virtualLeds);
// }
