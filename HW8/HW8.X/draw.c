#include "draw.h"

void draw_letter(unsigned char x, unsigned char y, unsigned char fig){
    
    unsigned char letter;
    
    for(int i=0; i<=4; i++){
        for(int j = 0; j<=7; j++){
            letter = ASCII[fig][i] >> j;
            letter = letter & 0b00000001;
            if(letter == 0b00000001){
                ssd1306_drawPixel(x+i,j,1);}
                
            else if(letter == 0){}
        }
    }
    ssd1306_update();
}