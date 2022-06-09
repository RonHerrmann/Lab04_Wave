#include "dac.h"
#include "types.h"



// tristate register
#define DAC_CS_TRIS TRISDbits.TRISD8
#define DAC_SDI_TRIS TRISBbits.TRISB10
#define DAC_SCK_TRIS TRISBbits.TRISB11
#define DAC_LDAC_TRIS TRISBbits.TRISB13

// port register
#define DAC_CS_PORT PORTDbits.RD8
#define DAC_SDI_PORT PORTBbits.RB10
#define DAC_SCK_PORT PORTBbits.RB11
#define DAC_LDAC_PORT PORTBbits.RB13

// analog to digital converter 1 port configuration register
#define DAC_SDI_AD1CFG AD1PCFGLbits.PCFG10
#define DAC_SCK_AD1CFG AD1PCFGLbits.PCFG11
#define DAC_LDAC_AD1CFG AD1PCFGLbits.PCFG13

// analog to digital converter 2 port configuration register
#define DAC_SDI_AD2CFG AD2PCFGLbits.PCFG10
#define DAC_SCK_AD2CFG AD2PCFGLbits.PCFG11
#define DAC_LDAC_AD2CFG AD2PCFGLbits.PCFG13

void dac_initialize()
{
    SETBIT(DAC_SDI_AD1CFG);
    SETBIT(DAC_SDI_AD2CFG);  // set AN10 to digital mode
    
    SETBIT(DAC_SCK_AD1CFG);
    SETBIT(DAC_SCK_AD2CFG); // set AN11 to digital mode
    
    SETBIT(DAC_LDAC_AD1CFG);
    SETBIT(DAC_LDAC_AD2CFG); // set AN13 to digital mode
    
    // this means AN10 will become RB10, AN11->RB11, AN13->RB13
    // see datasheet 11.3
    
    
    CLEARBIT(DAC_CS_TRIS);
    CLEARBIT(DAC_SDI_TRIS);
    CLEARBIT(DAC_SCK_TRIS); 
    CLEARBIT(DAC_LDAC_TRIS);    // set RD8, RB10, RB11, RB13 as output pins
    
    // set default state: CS=on, SCK=off, SDI=off, LDAC=on
     
    SETBIT(DAC_CS_PORT); // high to enable 
    CLEARBIT(DAC_SCK_PORT); // write on rising edge
    CLEARBIT(DAC_SDI_PORT); // Bit to send Data to DAC
    SETBIT(DAC_LDAC_PORT);  // set default state: CS=1, SCK=0, SDI=undefined, LDAC=1 (Datasheet MCP4822 Page 23)
   
}


void dac_convert_milli_volt(uint16_t milliVolt)
{
    CLEARBIT(DAC_CS_PORT);  // Set CS bit to zero to start conversation
    
    uint8_t var = 16;
    
    for(var; var >= 1; var--){      // Set Binary-Code for Output signal by setting SDI Bit high or low
        
        Nop();
        CLEARBIT(DAC_SCK_PORT);
        Nop();
        
        DAC_SDI_PORT = milliVolt >> (var -1) & BV(0);
        
        Nop();
        SETBIT(DAC_SCK_PORT);  
    }
}
