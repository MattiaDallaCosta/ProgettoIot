#include "boardDrivers.h"

float_t joyAngle(void){
    int16_t x = ADC14_getResult(ADC_MEM0) - 8192;
    int16_t y = ADC14_getResult(ADC_MEM1) - 8192;
    float_t mod = sqrt(x*x + y*y);
    return acos(x/mod);
}
float_t accelAngle(void){
    int16_t x = ADC14_getResult(ADC_MEM2) - 8192;
    int16_t y = ADC14_getResult(ADC_MEM3) - 8192;
    float_t mod = sqrt(x*x + y*y);
    return acos(x/mod);
}
float_t accelModule(void){
    int16_t x = ADC14_getResult(ADC_MEM2) - 8192;
    int16_t y = ADC14_getResult(ADC_MEM3) - 8192;
    return sqrt(x*x + y*y);
}

void LCDInit(void){
    Crystalfontz128x128_Init();
}

uint8_t pixInCircle(uint8_t x ,uint8_t y, Entity circ){
    uint8_t mod = sqrt((x - GETX(circ))*(x - GETX(circ)) + (y - GETY(circ))*(y - GETY(circ)))
    if(mod <= GETRAD(circ)) return 1
    return 0
}
