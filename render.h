#use delay(clock=4M)

#byte PORTA = getenv("SFR:PORTA")
#byte TRISA = getenv("SFR:TRISA")
#byte DATABYTE = getenv("SFR:PORTB")
#byte TRIS_DATA = getenv("SFR:TRISB")
#byte STATUS = getenv("SFR:STATUS")
#bit RP0 = STATUS.5
#bit RP1 = STATUS.6
#bit RS = PORTA.0
#bit TRIS_RS = TRISA.0
#bit RW = PORTA.1
#bit TRIS_RW = TRISA.1
#bit CS1 = PORTA.2
#bit TRIS_CS1 = TRISA.2
#bit CS2 = PORTA.3
#bit TRIS_CS2 = TRISA.3
#bit EN = PORTA.4
#bit TRIS_EN = TRISA.4

void setX(int8 x) {
   EN = 1;
   RS = 0;
   RW = 0;
   DATABYTE = 0b01000000 | x;
   EN = 0;
}

void setLine(int8 l) {
   EN = 1;
   RS = 0;
   RW = 0;
   DATABYTE = 0b10111000 | l;
   EN = 0;
}

void writeData(int8 test) {
   EN = 1;
   RS = 1;
   RW = 0;
   DATABYTE = test;
   delay_ms(1);
   EN = 0;
}

void initialTRIS() {
   TRIS_RS = 0;
   TRIS_RW = 0;
   TRIS_CS1 = 0;
   TRIS_CS2 = 0;
   TRIS_EN = 0;
   TRIS_DATA = 0;
}

void start(){
   initialTRIS();
   
   int8 test = 0b11111011;
   int8 x = 0;
   int8 line = 0;
//!   setX(0);
   while(1){
      CS1 = 1;
      CS2 = 0;
      setX(x);
//!      delay_us(2);
      setLine(line);
//!      delay_us(1);
      writeData(test);
//!      delay_us(10);
      x++;
      if (x > 64) {
         x = 0;
         line++;
         if (line > 8)
            line = 0;
      }
   }
}

void initialBoard() {
   CS1 = 0;
   CS2 = 1;

   for(int i = 0;i < 8; i++) {
      setX(0);
      setLine(i);
      writeData(0xffff);
   }
}
   
/**
 * x; 0 - 15
 * y; 0 - 15
*/
void setPosition(int8 x, int8 y) {
   setX(x*4);
   setLine(y/2);
}

void createBall(int8 x, int8 y) {
   // create ball 4x4 ps
   setPosition(x, y);
   for(int i = 0; i < 4; i++) {
      if (y%2 == 0)
         writeData(0b00001111);
      else 
         writeData(0b11110000);
   }
}

void clearBall(int8 x, int8 y) {
   setPosition(x, y);
   for(int i = 0; i < 4; i++) {
      writeData(0b00000000);
   }
}

void initialLine() {
   CS1 = 1;
   CS2 = 0;
   
   for(int i = 0; i < 16; i++) {
      createBall(i, 0);
      createBall(i, 15);
   }
}
