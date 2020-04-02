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

#use delay(clock=4M)

#byte PORTC = getenv("SFR:PORTB")
#byte TRIS_PORTC = getenv("SFR:TRISB")
#byte PORTB = getenv("SFR:PORTC")
#byte TRIS_PORTB = getenv("SFR:TRISC")
#byte STATUS = getenv("SFR:STATUS")
#bit RP0 = STATUS.5
#bit RP1 = STATUS.6
#bit PORTC0 = PORTC.0
#bit PORTC1 = PORTC.1
#bit PORTC3 = PORTC.3
#bit PORTC4 = PORTC.4

int prevC04 = 0;
int prevC14 = 0;

void setOutput(){
   TRIS_PORTB = 0b00000000;
   TRIS_PORTC = 0b11110000;
}

void setLight(){
   PORTB = 0x01;
   PORTC = 0x01;
}

#INT_TIMER1
void timer1_isr() {
   set_timer1(65036); // re-set the timer1 counter to maintain a stable period
   if(PORTC3 == 0b1) PORTC = 0x01;
   else PORTC = PORTC << 1;
}

void join(){
   if (prevC04 == 0 && PORTC == 0b00010001) {
      PORTB = PORTB << 1;
      prevC04 = 1;
   }
   if (prevC04 == 1 && PORTC == 0b00000001) {
      PORTB = PORTB << 1;
      prevC04 = 0;
   }
   if (prevC14 == 0 && PORTC == 0b00010010) {
      PORTB = PORTB >> 1;
      prevC14 = 1;
   }
   if (prevC14 == 1 && PORTC == 0b00000010) {
      PORTB = PORTB >> 1;
      prevC14 = 0;
   }
}

void main(){

   setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
   set_timer1(65036);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   
   setOutput();
   setLight();
   
   while(1){
     join();
   }
}

