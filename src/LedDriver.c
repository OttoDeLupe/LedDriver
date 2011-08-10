#include "LedDriver.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <memory.h>

/* static local variables */

static uint16_t * ledAddress;
static uint16_t ledImage;

enum {ALL_LEDS_ON = 0xffff, ALL_LEDS_OFF = 0};
enum {FIRST_LED = 1, LAST_LED = 16};

/*****
   Helper Functions
****/
static uint16_t ConvertLEDNumToBit(int ledNum)
{
	return 1 << (ledNum - 1);
}

static void UpdateHardware(void)
{
  *ledAddress = ledImage;
}

static bool LedOutOfBounds(int ledNum)
{
  return (ledNum < FIRST_LED || ledNum > LAST_LED);
}

static void SetLedImageBit(int ledNum)
{
  ledImage |= ConvertLEDNumToBit(ledNum);
}

static void ClearLedImageBit(int ledNum)
{
  ledImage &= ~(ConvertLEDNumToBit(ledNum));
}

/*****
   Driver Functions
****/
void LedDriver_Create(uint16_t *address)
{
  ledAddress = address;
  ledImage = ALL_LEDS_OFF;
  UpdateHardware();
}

void LedDriver_TurnOnLED(int ledNum)
{
  if (LedOutOfBounds(ledNum))
    return;
  
  SetLedImageBit(ledNum);
  UpdateHardware();
}

void LedDriver_TurnOffLED(int ledNum)
{
  if (LedOutOfBounds(ledNum))
    return;
  
  ClearLedImageBit(ledNum);
  UpdateHardware();
}

void LedDriver_TurnAllOn(void)
{
  ledImage = ALL_LEDS_ON;
  UpdateHardware();
}

void LedDriver_TurnAllOff(void)
{
  ledImage = ALL_LEDS_OFF;
  UpdateHardware();
}

bool LedDriver_IsOn(int ledNum)
{
  if (LedOutOfBounds(ledNum))
    return false;
  
  return ledImage & (ConvertLEDNumToBit(ledNum)); 

}

bool LedDriver_IsOff(int ledNum)
{
  return ! LedDriver_IsOn(ledNum);
}

void LedDriver_Destroy(void)
{
}


