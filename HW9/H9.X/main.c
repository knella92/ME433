#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "ws2812b.h"
#include "ssd1306.h"
#include "font.h"


// DEVCFG0
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
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations



//void blink();

int main() {

    __builtin_disable_interrupts(); // disable interrupts while initializing things

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
//    TRISAbits.TRISA4 = 0;
//    TRISBbits.TRISB4 = 1;
//    LATAbits.LATA4 = 0;
    
    i2c_master_setup();
    ws2812b_setup();
    ssd1306_setup();
    
    __builtin_enable_interrupts();
    
    //wsColor colors = HSBtoRGB(30.0,1.0,1.0);
    //unsigned char message[100];
    //wsColor colors[3];
    wsColor colors[5];
    float hue1 = 0.0, hue2 = 60.0, hue3 = 120.0, hue4 = 180.0, hue5 = 240.0;
    colors[0] = HSBtoRGB(hue1, 1.0, 1.0);
    colors[1] = HSBtoRGB(hue2, 1.0, 1.0);
    colors[2] = HSBtoRGB(hue3, 1.0, 1.0);
    colors[3] = HSBtoRGB(hue4, 1.0, 1.0);
    colors[4] = HSBtoRGB(hue5, 1.0, 1.0);
    
    ws2812b_setColor(colors, 5);
    float incr = 0.05;
    
    while (1) {
        hue1 = hue1 + incr; hue2 = hue2 + incr; hue3 = hue3 + incr; hue4 = hue4 + incr; hue5 = hue5 + incr;
        
        if(hue1>359.9){
            hue1 = 0.0;
        }
        if(hue2>359.9){
            hue2 = 0.0;
        }
        if(hue3>359.9){
            hue3 = 0.0;
        }
        if(hue4>359.9){
            hue4 = 0.0;
        }
        if(hue5>359.9){
            hue5 = 0.0;
        }
        
        colors[0] = HSBtoRGB(hue1, 1.0, 1.0);
        colors[1] = HSBtoRGB(hue2, 1.0, 1.0);
        colors[2] = HSBtoRGB(hue3, 1.0, 1.0);
        colors[3] = HSBtoRGB(hue4, 1.0, 1.0);
        colors[4] = HSBtoRGB(hue5, 1.0, 1.0);

        ws2812b_setColor(colors, 5);

        
    }
}



//void blink(){
//    LATAbits.LATA4 = 1;
//    _CP0_SET_COUNT(0);
//    while(_CP0_GET_COUNT()<24000000/2/20){}
//    LATAbits.LATA4 = 0;
//
//    _CP0_SET_COUNT(0);
//    while(_CP0_GET_COUNT()<24000000/2/20){}
//    
//}
//
