#ifndef D_LedDriver_H
#define D_LedDriver_H
#include <stdbool.h>
#include <stdint.h>
/*
  LedDriver is responsible for ...
*/


void LedDriver_Create(uint16_t *address);
void LedDriver_Destroy(void);

void LedDriver_TurnOnLED(int ledNum);
void LedDriver_TurnOffLED(int ledNum);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);
bool LedDriver_IsOn(int ledNum);
bool LedDriver_IsOff(int ledNum);

#endif  /* D_LedDriver_H */
