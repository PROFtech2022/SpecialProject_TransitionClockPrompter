/*
LED Driver Library ---> SN74HC595
by: Kenny Neutron
12-02-2022
*/

#include "LEDdriver.h"

LEDdriver::LEDdriver() {
  //NOP
}

void LEDdriver::begin(byte dataPIN, byte clockPIN, byte strobePIN) {
  pinMode(dataPIN, OUTPUT);
  pinMode(clockPIN, OUTPUT);
  pinMode(strobePIN, OUTPUT);

  datPin = dataPIN;
  clkPin = clockPIN;
  strPin = strobePIN;

  digitalWrite(datPin, 0);
  digitalWrite(clkPin, 0);
  digitalWrite(strPin, 0);
}


void LEDdriver::latchData() {
  digitalWrite(strPin, 1);
  delayMicroseconds(10);
  digitalWrite(strPin, 0);
  delayMicroseconds(10);
}

void LEDdriver::regData(byte DataToReg) {
  shiftOut(datPin, clkPin, LSBFIRST, DataToReg);
}

void LEDdriver::printNum(byte NumToPrint) {
  switch (NumToPrint) {
    case 0:
      regData(0b00000011);
      break;
    case 1:
      regData(0b10011111);
      break;
    case 2:
      regData(0b00100101);
      break;
    case 3:
      regData(0b00001101);
      break;
    case 4:
      regData(0b10011001);
      break;
    case 5:
      regData(0b01001001);
      break;
    case 6:
      regData(0b01000001);
      break;
    case 7:
      regData(0b00011111);
      break;
    case 8:
      regData(0b00000001);
      break;
    case 9:
      regData(0b00001001);
      break;
    case 10:  //P
      regData(0b00110001);
      break;
    case 11:  //O
      regData(0b11000101);
      break;

    case 100:
      regData(0b00000010);
      break;
    case 101:
      regData(0b10011110);
      break;
    case 102:
      regData(0b00100100);
      break;
    case 103:
      regData(0b00001100);
      break;
    case 104:
      regData(0b10011000);
      break;
    case 105:
      regData(0b01001000);
      break;
    case 106:
      regData(0b01000000);
      break;
    case 107:
      regData(0b00011110);
      break;
    case 108:
      regData(0b00000000);
      break;
    case 109:
      regData(0b00001000);
      break;
    case 110:  //P
      regData(0b00110000);
      break;
    case 255:  //OFF
      regData(0b11111111);
      break;
  }
}



void LEDdriver::printByte(byte ByteToPrint){

   // printNum(ByteToPrint)

   if(ByteToPrint>=100){
      //Display 100+

      //PrintTens + 1/2 of 1
      printNum(((ByteToPrint%100)/10)+100);
      
      //PrintOnes + 1/2 of 1
      printNum((ByteToPrint%10)+100);
   }

   if(ByteToPrint>=10 && ByteToPrint<100){
        //PrintTens
        printNum(ByteToPrint/10);

        //PrintOnes
        printNum(ByteToPrint%10);
   }

   if(ByteToPrint<10){
    //OffTens
        printNum(255);
    //PrintOnes
        printNum(ByteToPrint);
   }

}

void LEDdriver::printOneDigit(byte DigitToPrint){
    printNum(DigitToPrint);
}