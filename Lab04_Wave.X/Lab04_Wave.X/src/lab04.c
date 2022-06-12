#include "lab04.h"

#include <xc.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>

#include "math.h"

#include "types.h"
#include "lcd.h"
#include "led.h"
#include "dac.h"

// signal parameter

#define sineWaveFrequency_Hz 1
#define sampleRate_Hz 50
#define minimalVoltage 3
#define maximalVoltage 1

// macros

#define getPR3(sampleRate) ((12.8e6 * (1/sampleRate)) / 256)
#define getSampleTime(sampleRate) (1/sampleRate)
#define getAmplitude(minVolatage, maxVoltage) (((maxVoltage - minVoltage) / 2)*1000)
#define getOmega(frequency) (2 * pi * frequency)
#define getSinePeriodTime(frequency) (1/frequency)


/*
 * Timer code
 */
    
#define TCKPS_1   0x00
#define TCKPS_8   0x01
#define TCKPS_64  0x02
#define TCKPS_256 0x03


volatile uint16_t V_out = 0;
volatile uint16_t currentTime = 0;

void timer_initialize()  // Timer 3
{   
      
   T3CONbits.TON = 0; // Disable the Timers
   T3CONbits.TCKPS = TCKPS_256; // Set Prescaler 1:1
   T3CONbits.TCS = 0; // Set Clock Source (internal = 0)
   T3CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating //this line can be ignored, if TCS =  1 (have a look at the manual)  
   PR3 = getPR3(sampleRate_s); // Load Timer Periods 
   TMR3 = 0x00; // Reset Timer Values
   IPC2bits.T3IP = 0x01; // Set Interrupt Priority (actually Level 1)
   CLEARBIT(IFS0bits.T3IF); //= 0; // Clear Interrupt Flags
   IEC0bits.T3IE = 1; // Enable Interrupts --> (important: all)
   T3CONbits.TON = 1; // Enable the Timers  
}

// interrupt service routine

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T3Interrupt(void)
{   
    
    currentTime = currentTime + getSampleTime(sampleRate_Hz);  // calculate time for sine wave
    
    TOGGLELED(LED1_PORT);       // toggle LED1
    
    V_out = getAmplitude(minimalVoltage, maximalVoltage) * sin(getOmega(sineWaveFrequency_Hz) * currentTime) + (minimalVoltage*1000);    // Vout = Vamplitude * sin(omega_signal * t) + Voffset, with omega_signal = 2 * pi * f_signal
    
    dac_convert_milli_volt(V_out);  // set output voltage to DAC
    
    IFS0bits.T3IF = 0;      // clear interupt service routin flag
}

/*
 * main loop
 */

void main_loop()
{
    // print assignment information
    lcd_printf("Lab04: Wave");
    lcd_locate(0, 1);
    lcd_printf("Group: Boyang & Ron");
    
    CLEARBIT(LED1_TRIS);   //set LED1 as output
    
    while(TRUE) {   
        
        if(currentTime == getSinePeriodTime(sineWaveFrequency_Hz){
            
            currentTime = 0;        // restet current time, because one sine period is over 
        }
                
    }
}

