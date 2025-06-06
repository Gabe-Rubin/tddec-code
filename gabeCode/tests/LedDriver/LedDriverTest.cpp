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

TEST(LedDriver, TurnOnMultipleLeds)
{
    ledDriver0->turnOn(9);
    ledDriver0->turnOn(8);
    LONGS_EQUAL(0x0180, virtualLeds);
}

TEST(LedDriver, TurnOffMultipleLeds)
{
    ledDriver0->turnAllOn();
    ledDriver0->turnOff(9);
    ledDriver0->turnOff(8);
    LONGS_EQUAL((~0x0180)&0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
    ledDriver0->turnAllOn();
    ledDriver0->turnOff(8);
    LONGS_EQUAL(0xff7f, virtualLeds);
}

TEST(LedDriver, AllOn)
{
    ledDriver0->turnAllOn();
    LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, AllOff)
{
    ledDriver0->turnAllOn();
    ledDriver0->turnAllOff();
    LONGS_EQUAL(0x0000, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
    virtualLeds = 0xffff;
    ledDriver0->turnOn(8);
    LONGS_EQUAL(0x0080, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
    ledDriver0->turnOn(1);
    ledDriver0->turnOn(16);
    LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
    ledDriver0->turnOn(-1);
    ledDriver0->turnOn(0);
    ledDriver0->turnOn(17);
    ledDriver0->turnOn(3141);
    LONGS_EQUAL(0x0000, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
    ledDriver0->turnAllOn();
    ledDriver0->turnOff(0);
    ledDriver0->turnOff(-1);
    ledDriver0->turnOff(-9203);
    ledDriver0->turnOff(17);
    ledDriver0->turnOff(3141);
    LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
    ledDriver0->turnOn(-1);
    STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
    CHECK_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

IGNORE_TEST(LedDriver, OutOfBoundsToDo)
{
    // This is an example of an EXECUTABLE REMINDER
    // Maybe we couldn't decide how we wanted to handle
    // an out-of-bounds LED value.
    // We can add a test like this to remember to come back to it.

    /* TODO: What should we do during runtime? */
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
    CHECK_FALSE(ledDriver0->isOn(0))
    CHECK_FALSE(ledDriver0->isOn(17))
    CHECK_TRUE(ledDriver0->isOff(0));
    CHECK_TRUE(ledDriver0->isOff(17));
}

TEST(LedDriver, IsOn)
{
    CHECK_FALSE(ledDriver0->isOn(1));
    ledDriver0->turnOn(1);
    CHECK_TRUE(ledDriver0->isOn(1));
}

TEST(LedDriver, IsOff)
{
    CHECK_TRUE(ledDriver0->isOff(9));
    ledDriver0->turnOn(9);
    CHECK_FALSE(ledDriver0->isOff(9));
}
