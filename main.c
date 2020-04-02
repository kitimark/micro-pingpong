//!#include <16F886.h>
#include "lib.h" // render lib

#use delay(clock=4M)


void bounchBall() {
   int8 x = 0;
   int8 y = 1;
   
   int8 xVector = 1;
   int8 yVector = 1;

   while (1) {
      createBall(x, y);
      clearBall(x, y);
      
      // calculate next position
      if (x == 15) xVector = -1;
      if (x == 0) xVector = 1;
      x += xVector;
      
      if (y == 14) yVector = -1;
      if (y == 1) yVector = 1;
      y += yVector;
   }
}

void main() {
   initialTRIS();
   initialBoard();
   initialLine();
   
   CS1 = 1;
   CS2 = 0;
   
   // wait for intial glcd module
   delay_us(1000);
   
   bounchBall();
   
//!   while(1) {
//!      for(int i = 0; i < 16; i++) {
//!         createBall(i, i);
//!         clearBall(i, i);
//!      }
//!   }
}
