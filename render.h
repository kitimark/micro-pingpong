#use delay(clock=4M)

#byte PORTA = getenv("SFR:PORTA")
#byte TRISA = getenv("SFR:TRISA")
#byte DATABYTE = getenv("SFR:PORTB")
#byte TRIS_DATA = getenv("SFR:TRISB")
#byte STATUS = getenv("SFR:STATUS")
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

void createPixel(int8 x, int8 y) {
   // create ball 4x4 ps
   setPosition(x, y);
   for(int i = 0; i < 4; i++) {
      if (y%2 == 0)
         writeData(0b00001111);
      else 
         writeData(0b11110000);
   }
}

void clearPixel(int8 x, int8 y) {
   setPosition(x, y);
   for(int i = 0; i < 4; i++) {
      writeData(0b00000000);
   }
}

void clearBall(int8 x, int8 y) {
   setPosition(x, y);
   for(int i = 0; i < 4; i++) {
      if (y == 1 && (x >= player1 && x < player1 + 4)) {
         writeData(0b00001111);
      }
      else if (y == 14 && (x >= player2 && x < player2 + 4)) {
         writeData(0b11110000);
      }
      else writeData(0b00000000);
   }
}

void initialLine() {
   CS1 = 1;
   CS2 = 0;
   
   for(int i = 0; i < 16; i++) {
      createPixel(i, 0);
      createPixel(i, 15);
   }
}

void createBoard(x, y) {
   for (int i = 0; i < 4; i++) {
      createPixel(x + i, y);
   }
}

// player 1
void moveBoardPlayer1Left() {
   player1 -= 1;
   createPixel(player1, 0);
   clearPixel(player1 + 4, 0);
}

void moveBoardPlayer1Right() {
   player1 += 1;
   createPixel(player1 + 3, 0);
   clearPixel(player1 - 1, 0);
}

// player 2
void moveBoardPlayer2Left() {
   player2 -= 1;
   createPixel(player2, 15);
   clearPixel(player2 + 4, 15);
}

void moveBoardPlayer2Right() {
   player2 += 1;
   createPixel(player2 + 3, 15);
   clearPixel(player2 - 1, 15);
}
