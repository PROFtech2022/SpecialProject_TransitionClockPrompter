/*
LED Driver Library ---> SN74HC595
by: Kenny Neutron
12-02-2022
*/

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "Arduino.h"


class LEDdriver{

    public:
        LEDdriver();

        void begin(byte dataPIN, byte clockPIN, byte strobePIN);

        void latchData();
        
        void regData(byte DataToReg);

        void printNum(byte NumToPrint);

        void printByte(byte ByteToPrint);

        void printOneDigit(byte DigitToPrint);

    private:
        byte datPin, clkPin, strPin;

        

};

#endif