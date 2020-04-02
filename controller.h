#use delay(clock=4M)

#byte PORTC = getenv("SFR:PORTC")
#byte TRIS_PORTC = getenv("SFR:TRISC")
#byte PORTB = getenv("SFR:PORTB")
#byte TRIS_PORTB = getenv("SFR:TRISB")
#bit PORTC0 = PORTC.0
#bit PORTC1 = PORTC.1
#bit PORTC2 = PORTC.2
#bit PORTC3 = PORTC.3
#bit PORTC4 = PORTC.4

int8 prevC04 = 0;
int8 prevC14 = 0;

int8 prevC05 = 0;
int8 prevC15 = 0;

void counterColumeController() {
   if(PORTC1 == 0b1) {
      PORTC0 = 0b1;
      PORTC1 = 0b0;
      PORTC2 = 0b1;
      PORTC3 = 0b0;
   }
   else PORTC = PORTC << 1;
}

void initialController() {
   TRIS_PORTC = 0b11110000;
   PORTC = 0b00000101;
}

void controller() {
   // player 1 left
   if (prevC04 == 0 && PORTC == 0b00010101) {
//!      moveBoardPlayer1Left();
      prevC04 = 1;
   }
   if (prevC04 == 1 && PORTC == 0b00000101) {
      moveBoardPlayer1Left();
      prevC04 = 0;
   }
   
   // player 1 right
   if (prevC14 == 0 && PORTC == 0b00011010) {
//!      PORTB = PORTB >> 1;
//!      moveBoardPlayer1Right();
      prevC14 = 1;
   }
   if (prevC14 == 1 && PORTC == 0b00001010) {
//!      PORTB = PORTB >> 1;
      moveBoardPlayer1Right();
      prevC14 = 0;
   }
   
      // player 2 left
   if (prevC05 == 0 && PORTC == 0b00100101) {
//!      moveBoardPlayer2Left();
      prevC05 = 1;
   }
   if (prevC05 == 1 && PORTC == 0b00000101) {
      moveBoardPlayer2Left();
      prevC05 = 0;
   }
   
   // player 2 right
   if (prevC15 == 0 && PORTC == 0b00101010) {
//!      moveBoardPlayer2Right();
      prevC15 = 1;
   }
   if (prevC15 == 1 && PORTC == 0b00001010) {
      moveBoardPlayer2Right();
      prevC15 = 0;
   }
}

