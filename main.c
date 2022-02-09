#include "msp.h"
#include <stdio.h>
#include <math.h>
#include "ti/devices/msp432p4xx/driverlib/driverlib.h"
#include "ti/grlib/grlib.h"
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

#include "gameComponents.h"
#include "boardDrivers.h"

#define NUMCLAS 4

Graphics_Context gcon;
DinArray classes[NUMCLAS];
void (*behav[NUMCLAS])(Entity);
Entity player;

void main(void)
{

    // Watchdog timer
    WDT_A_holdTimer();

    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P5,GPIO_PIN1);
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P3,GPIO_PIN5);
    //GPIO_setAsInputPin(GPIO_PORT_P5,GPIO_PIN1); // bottone 1
    //GPIO_setAsInputPin(GPIO_PORT_P3,GPIO_PIN5);// bottone 2
    GPIO_enableInterrupt(GPIO_PORT_P5,GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P3,GPIO_PIN5);
    GPIO_registerInterrupt(GPIO_PORT_P5,port5_isr);
    GPIO_registerInterrupt(GPIO_PORT_P3,port3_isr);
    adcInit();
    clkInit();
    // parte grafica
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_setBackgroundColor(&gcon, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(&gcon, GRAPHICS_COLOR_WHITE);
    Graphics_setFont(&gcon, &g_sFontCm12);

    Graphics_drawStringCentered(&gcon, "GAY", 3, 30, 30, 0);


    playing = 1;

    while(playing){
        PCM_gotoLPM0();
    }
}

void port3_isr(){
      uint32_t stato = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
      GPIO_clearInterruptFlag(GPIO_PORT_P3, stato);
      if (stato & GPIO_PIN5){
         //...
      }
}
void port5_isr(){
    uint32_t stato = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    GPIO_clearInterruptFlag(GPIO_PORT_P5, stato);
    if (stato & GPIO_PIN1){
        //...
    }
}

void adcInit(){
    /* Configures Pin 6.0 and 4.4 as ADC input */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);   // joy x
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);   // joy y
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);   // accel x
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);   // accel y
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);   // accel z

    /* Initializing ADC (ADCOSC/64/8) */
        ADC14_enableModule();
        ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);

        /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A15, A9)  with repeat)
             * with internal 2.5v reference */
        ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM4, true);

        ADC14_configureConversionMemory(ADC_MEM0,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

        ADC14_configureConversionMemory(ADC_MEM1,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

        ADC14_configureConversionMemory(ADC_MEM2,
                        ADC_VREFPOS_AVCC_VREFNEG_VSS,
                        ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);

        ADC14_configureConversionMemory(ADC_MEM3,
                               ADC_VREFPOS_AVCC_VREFNEG_VSS,
                               ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);

        ADC14_configureConversionMemory(ADC_MEM4,
                               ADC_VREFPOS_AVCC_VREFNEG_VSS,
                               ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);

        /* Enabling the interrupt when a conversion on channel 1 (end of sequence)
         *  is complete and enabling conversions */
        ADC14_enableInterrupt(ADC_INT0);
               ADC14_enableInterrupt(ADC_INT1);
               ADC14_enableInterrupt(ADC_INT2);
               ADC14_enableInterrupt(ADC_INT3);
               ADC14_enableInterrupt(ADC_INT4);

        /* Enabling Interrupts */
        Interrupt_enableInterrupt(INT_ADC14);
        Interrupt_enableMaster();

        /* Setting up the sample timer to automatically step through the sequence
         * convert.
         */
        ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

        /* Triggering the start of the sample */
        ADC14_enableConversion();
        ADC14_toggleConversionTrigger();
}

void ADC14_IRQHandler(){

    uint64_t stato = ADC14_getInterruptStatus();
    ADC14_clearInterruptFlag(stato);

    switch(stato){
        case(ADC_INT0):
        //if(ADC14_getResult(ADC_MEM0)/10 > values[0][0]) values[0][0] = ADC14_getResult(ADC_MEM0)/10;
        //if(ADC14_getResult(ADC_MEM0)/10 < values[0][1]) values[0][1] = ADC14_getResult(ADC_MEM0)/10;
               break;
        case(ADC_INT1):
        //if(ADC14_getResult(ADC_MEM1)/10 > values[1][0]) values[1][0] = ADC14_getResult(ADC_MEM1)/10;
        //if(ADC14_getResult(ADC_MEM1)/10 < values[1][1]) values[1][1] = ADC14_getResult(ADC_MEM1)/10;
               break;
        case(ADC_INT2):
        xres=ADC14_getResult(ADC_MEM2);
        //if(ADC14_getResult(ADC_MEM2)/10 > values[2][0]) values[2][0] = ADC14_getResult(ADC_MEM2)/10;
        //if(ADC14_getResult(ADC_MEM2)/10 < values[2][1]) values[2][1] = ADC14_getResult(ADC_MEM2)/10;
                       break;
        case(ADC_INT3):
        //if(ADC14_getResult(ADC_MEM3)/10 > values[3][0]) values[3][0] = ADC14_getResult(ADC_MEM3)/10;
        //if(ADC14_getResult(ADC_MEM3)/10 < values[3][1]) values[3][1] = ADC14_getResult(ADC_MEM3)/10;
                       break;
        case(ADC_INT4):
        //if(ADC14_getResult(ADC_MEM4)/10 > values[4][0]) values[4][0] = ADC14_getResult(ADC_MEM4)/10;
        //if(ADC14_getResult(ADC_MEM4)/10 < values[4][1]) values[4][1] = ADC14_getResult(ADC_MEM4)/10;
                       break;
        default:
            break;
    }

}

void clkInit(){
    FPU_enableModule();
    CS_setDCOCenteredFrequency(20000);
    SysTick_enableModule();
    SysTick_setPeriod(4165000);
    Interrupt_enableSleepOnIsrExit();
    SysTick_enableInterrupt();
}

void SysTick_Handler(void) //game loop
{
    Graphics_flushBuffer(&gcon);
}


