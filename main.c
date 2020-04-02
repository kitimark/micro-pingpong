//!#include <16F886.h>
#include "lib.h" // render lib

#use delay(clock=4M)

void main() {
   initialTRIS();
   initialBoard();
   initialLine();
   
   CS1 = 1;
   CS2 = 0;
   
   // wait for intial glcd module
   delay_us(1000);
   
   while(1) {
      for(int i = 0; i < 16; i++) {
         createBall(i, i);
         clearBall(i, i);
      }
   }
}
