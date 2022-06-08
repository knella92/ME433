#include "font.h"
#include <xc.h>
#include "ssd1306.h"


void blink(){
    LATAbits.LATA4 = 1;
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<24000000/2/20){}
    LATAbits.LATA4 = 0;

    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<24000000/2/20){}
    
}


void drawCharacter(unsigned char x, unsigned char y, unsigned char fig){
    
    unsigned char dec_eq = fig - 32;
    
    unsigned char letter;
    
    for(int i=0; i<=4; i++){
        for(int j = 0; j<=7; j++){
            letter = ASCII[dec_eq][i] >> j;
            letter = letter & 0b00000001;
            if(letter == 0b00000001){
                ssd1306_drawPixel(x+i,y+j,1);}
                
            else if(letter == 0){
                ssd1306_drawPixel(x+i,y+j,0);}
        }
    }

}

void drawMessage(unsigned char x, unsigned char y, unsigned char * figs){;
    int i = 0, k;
    while(figs[i] != '\0'){
        k = i*5 + 1;
        if (i < 25){
            drawCharacter(x+k,y,figs[i]);
        }
        else if (i < 50){
            drawCharacter(x+k - 125, y+8,figs[i]);
        }
        else if (i<75){
            drawCharacter(x+k - 250, y+16,figs[i]);

        }
        else if (i<100){
            drawCharacter(x+k - 375, y+24,figs[i]);
        }
        i++;
    }
    
    
}