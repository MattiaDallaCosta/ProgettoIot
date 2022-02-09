#pragma once

#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include "gameComponents.h"
#include <math.h>

void port3_isr(void);
void port5_isr(void);
void adcInit(void);
void clkInit(void);
void LCDInit(void);

float_t joyAngle(void);
float_t accelAngle(void);
float_t accelModule(void);
uint8_t pixInCircle(uint8_t, uint8_t, Entity);

