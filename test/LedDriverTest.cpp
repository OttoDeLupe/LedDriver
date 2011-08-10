extern "C"
{
#include "LedDriver.h"
}

/* CppUTest includes should be after your and system includes */
#include "CppUTest/TestHarness.h"

static uint16_t virtualLeds;

TEST_GROUP(LedDriver)
{
  void setup()
  {
    LedDriver_Create(&virtualLeds);
  }

  void teardown()
  {
    LedDriver_Destroy();
  }
};


TEST(LedDriver, LedsOffAfterCreate)
{
  uint16_t leds = 0xffff;
  LedDriver_Create(&leds);
  LONGS_EQUAL(0, leds);
}

TEST(LedDriver, TurnOnLEDOne)
{
  LedDriver_TurnOnLED(1);
  LONGS_EQUAL(0x01, virtualLeds);
}

TEST(LedDriver, TurnOffLEDOne)
{
  LedDriver_TurnOnLED(1);
  LedDriver_TurnOffLED(1);
  LONGS_EQUAL(0x00, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLED)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOffLED(8);
  LONGS_EQUAL(0xff7f, virtualLeds);
}

TEST(LedDriver, LedIsOn)
{
  // is it off? Should be off to start with
  CHECK(LedDriver_IsOff(11));
  LedDriver_TurnOnLED(11);
  // is it on?
  CHECK(LedDriver_IsOn(11));
}

TEST(LedDriver, CheckAllOn)
{
  LedDriver_TurnAllOn();
  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, CheckAllOff)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
  LONGS_EQUAL(0x0, virtualLeds);
}

TEST(LedDriver, ToggleLed)
{
  CHECK(LedDriver_IsOff(11));
  LedDriver_TurnOnLED(11);
  CHECK(LedDriver_IsOn(11));
  LedDriver_TurnOffLED(11);
  CHECK(LedDriver_IsOff(11));
}	

TEST(LedDriver, TurnOnMultipleLEDs)
{
  LedDriver_TurnOnLED(8);
  LedDriver_TurnOnLED(9);
  LONGS_EQUAL(0x0180, virtualLeds);
}


TEST(LedDriver, TurnOffMultipleLEDs)
{
  // Starting condition is all off
  // Turn all on, and then turn some off
  LedDriver_TurnAllOn();
  LONGS_EQUAL(0xffff, virtualLeds);
  LedDriver_TurnOffLED(8);
  LedDriver_TurnOffLED(9);
  LONGS_EQUAL(0xfe7f, virtualLeds);
}

TEST(LedDriver, LedMemoryNotReadable)
{
  virtualLeds = 0xffff;
  LedDriver_TurnOnLED(8);
  LONGS_EQUAL(0x80, virtualLeds);
}

TEST(LedDriver, UpperLowerBoundsCheck)
{
  LedDriver_TurnOnLED(1);
  LedDriver_TurnOnLED(16);
  LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver, SetBogusLEDsChangesNothing)
{
  LedDriver_TurnOnLED(-1);
  LedDriver_TurnOnLED(0);
  LedDriver_TurnOnLED(17);
  LedDriver_TurnOnLED(1024);
  LONGS_EQUAL(0x0, virtualLeds);
}

TEST(LedDriver, ClearBogusLEDsChangesNothing)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOffLED(-1);
  LedDriver_TurnOffLED(0);
  LedDriver_TurnOffLED(17);
  LedDriver_TurnOffLED(1024);
  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsLEDsAlwaysOff)
{
  CHECK(LedDriver_IsOn(0) == false);
  CHECK(LedDriver_IsOn(17) == false);
}
