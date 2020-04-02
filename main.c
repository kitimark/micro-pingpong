#include <16F886.h>
#device ADC=10 *=16
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin not enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES BROWNOUT                 //Brownout reset
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#FUSES INTRC_IO

#include "render.h" // render lib

#use delay(clock=4M)


const int8 startX = 0;
const int8 startY = 1;
const int8 endX = 15;
const int8 endY = 14;

int8 x = startX;
int8 y = startY;
int8 xVector = 1;
int8 yVector = 1;

int8 player1 = 6;
int8 player2 = 6;

void bounchBall() {

   createPixel(x, y);
   clearPixel(x, y);
   
   // calculate next position
   if (x == endX) xVector = -1;
   if (x == startX) xVector = 1;
   x += xVector;
   
   if (y == endY) yVector = -1;
   if (y == startY) yVector = 1;
   y += yVector;

}

void main() {
   initialTRIS();
   initialBoard();
//!   initialLine();
   
   CS1 = 1;
   CS2 = 0;
   
   // wait for intial glcd module
   delay_us(1000);
   
   // initial players' board
   createBoard(player1, 0);
   createBoard(player2, 15);
   
   while(1) {
      bounchBall();
   }
}
