#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "ssd1306.h"
#include "font.h"
#include "draw.h"


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



void blink();

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
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB4 = 1;
    LATAbits.LATA4 = 0;
    
    i2c_master_setup(); // init i2c
    ssd1306_setup(); // init oled display
    
    __builtin_enable_interrupts();

//    unsigned char figs[20] = "Mr. Morale and the  ";
//    unsigned char figs2[12] = "Big Steppers";
//    unsigned char figs3[5] = "-KDOT";
    
    unsigned char message[100];
    unsigned char msg[100];
    int iter = 0;
    float fps = 0;
    
    sprintf(message, "Mr. Morale and the Big   Steppers - KDOT Ya Bish", iter, fps);
    ssd1306_clear();
    drawMessage(0,0, message);
    ssd1306_update();
    
    while (1) {
        //blink();
        iter++;
        _CP0_SET_COUNT(0);

        sprintf(msg, "Sales: %d     FPS:%2.2f", iter, fps);
        //ssd1306_clear();
        drawMessage(0,0,message);
        drawMessage(0,16, msg);
        ssd1306_update();
        fps = 1.0/(_CP0_GET_COUNT()/24000000.0);
        
        
    }
}



//void blink(){
//    LATAbits.LATA4 = 1;
////    ssd1306_drawPixel(0,0,1);
////    ssd1306_update();
//    _CP0_SET_COUNT(0);
//    while(_CP0_GET_COUNT()<24000000/2/20){}
//    LATAbits.LATA4 = 0;
//
//    _CP0_SET_COUNT(0);
//    while(_CP0_GET_COUNT()<24000000/2/20){}
//    
//}
//
