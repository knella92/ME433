#include <xc.h>
#include<sys/attribs.h>  // __ISR macro
#include<stdio.h>
#include "spi.h"

#define PI 3.14159

// DEVCFG0 - SFRs - can only be changed by the SNAP
#pragma config DEBUG = OFF // disable debugging
#pragma config JTAGEN = OFF // disable jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // disable flash write protect
#pragma config BWP = OFF // disable boot write protect
#pragma config CP = OFF // disable code protect

// DEVCFG1
#pragma config FNOSC = FRCPLL // use fast frc oscillator with pll
#pragma config FSOSCEN = OFF // disable secondary oscillator
#pragma config IESO = OFF // disable switching clocks
#pragma config POSCMOD = OFF // primary osc disabled
#pragma config OSCIOFNC = OFF // disable clock output
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // disable clock switch and FSCM
#pragma config WDTPS = PS1048576 // use largest wdt value
#pragma config WINDIS = OFF // use non-window mode wdt
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz fast rc internal oscillator
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

// DEVCFG3
#pragma config USERID = 0xFFFF // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations

int main(){
    __builtin_disable_interrupts();
    
    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    
    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;
    
    //enable multi vector interrupts
    INTCONbits.MVEC = 0x1;
    
    //disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1;
    
    initSPI();
    
    __builtin_enable_interrupts();
    
    unsigned char tchannel = 1; unsigned char schannel = 0;
    int i = 0; int k = 0;
    float twave[100]; float swave[50]; float m;
    
    for(int j=0;j<100;j++){
        if(j<50){
        twave[j] = 3.3/50*j;
        }
        else{
            twave[j]= 3.3/50*(100-j);
        }
    }
    
    for(int j=0; j<50; j++){
        m = j;
        swave[j] = 1.65*sin(m/50.0*2*PI) + 1.65;
    }
    
        
    while(1){
        //send sine wave to channel 0
        LATAbits.LATA0 = 0; // bring CS low
        assembler(schannel, swave[k]);
        LATAbits.LATA0 = 1; // bring CS back to high
        
        //send triangle wave to channel 1
        LATAbits.LATA0 = 0; // bring CS low
        assembler(tchannel,twave[i]);
        LATAbits.LATA0 = 1; // bring CS back to high
        
        
        i++; k++;
        if(i==100){
            i = 0;
        }
        if(k == 50){
            k = 0;
        }
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / 200) {
             // this loop runs 100 times per second
        }
    }
}