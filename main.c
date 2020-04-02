//!#include <16F886.h>
#include "render.h" // render lib

#use delay(clock=4M)


void bounchBall(startX, startY, endX, endY) {
   int8 x = startX;
   int8 y = startY;
   
   int8 xVector = 1;
   int8 yVector = 1;

   while (1) {
      createBall(x, y);
      clearBall(x, y);
      
      // calculate next position
      if (x == endX) xVector = -1;
      if (x == startX) xVector = 1;
      x += xVector;
      
      if (y == endY) yVector = -1;
      if (y == startY) yVector = 1;
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
   
   bounchBall(0, 1, 15, 14);
   
//!   while(1) {
//!      for(int i = 0; i < 16; i++) {
//!         createBall(i, i);
//!         clearBall(i, i);
//!      }
//!   }
}
