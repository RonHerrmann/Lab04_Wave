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

#define sineWaveFrequency 0x00;
#define sampleRate 0x00;
#define minimalVoltage 0x00;
#define maximalVoltage 0x00;


/*
 * Timer code
 */
    
#define TCKPS_1   0x00
#define TCKPS_8   0x01
#define TCKPS_64  0x02
#define TCKPS_256 0x03

void timer_initialize()  // Timer 3
{
   T3CONbits.TON = 0; // Disable the Timers
   T3CONbits.TCKPS = TCKPS_1; // Set Prescaler 1:1
   T3CONbits.TCS = 0; // Set Clock Source (internal = 0)
   T3CONbits.TGATE = 0; // Set Gated Timer Mode -> don't use gating //this line can be ignored, if TCS =  1 (have a look at the manual)  
   PR3 = 10; // Load Timer Periods (highets value possible?)
   TMR3 = 0x00; // Reset Timer Values
   IPC2bits.T3IP = 0x01; // Set Interrupt Priority (actually Level 1)
   CLEARBIT(IFS0bits.T3IF); //= 0; // Clear Interrupt Flags
   IEC0bits.T3IE = 0; // Enable Interrupts --> (important: all)
   T3CONbits.TON = 1; // Enable the Timers  
}

/*
 * main loop
 */

void main_loop()
{
    // print assignment information
    lcd_printf("Lab04: Wave");
    lcd_locate(0, 1);
    lcd_printf("Group: GroupName");
    
    while(TRUE) { }
}

