#include <xc.h>
#include "spi.h"

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    // Turn of analog pins
    ANSELA = 0;
    ANSELB = 0;           
    // Make A0 an output pin for CS
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 1;
    //...
    // Set A1 SDO1
    RPA1Rbits.RPA1R = 0b0011;
    // Set SDI1 to B5
    //SDI1Rbits.SDI1R = 0001;

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 239; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
    SPI1BUF = o;
    while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
      ;
    }
    return SPI1BUF;
}

void assembler(unsigned char c, float voltage){
    unsigned short p = c<<15;
    unsigned short v; float vbin;
    if (voltage>= 0 && voltage< 3.3){
        vbin = voltage/(3.3/255.0);
        v = vbin;
    }
    else{
        v = 0;
    }
    p = p|0b111<<12;
    p = p|v<<4;
    spi_io(p>>8);
    spi_io(p);
}