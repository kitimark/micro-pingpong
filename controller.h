#use delay(clock=4M)

#byte PORTC = getenv("SFR:PORTC")
#byte TRIS_PORTC = getenv("SFR:TRISC")
#byte PORTB = getenv("SFR:PORTB")
#byte TRIS_PORTB = getenv("SFR:TRISB")
#bit PORTC0 = PORTC.0
#bit PORTC1 = PORTC.1
#bit PORTC3 = PORTC.3
#bit PORTC4 = PORTC.4

void counterColumeController() {
   if(PORTC3 == 0b1) {
      PORTC0 = 0b1;
      PORTC3 = 0b0;
   }
   else PORTC = PORTC << 1;
}

void initialController() {
   TRIS_PORTC = 0b11110000;
   PORTC0 = 0b1;
}
