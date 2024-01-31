/*
  Transition Clock Prompter Project

  Coded by: Kenny Neutron

  Date Started: 12-23-2023
  Date Finished: N/A

  Environment: Atmega328P-AU (Arduino Nano New(2022-Onwards) Bootloader)
  Repository: https://github.com/PROFtech2022/SpecialProject_TransitionClockPrompter
*/
#include <Stepper.h>
#include <FastLED.h>
#include "LEDdriver.h"
#include "Variables.h"

#define LED_DataPin 7
#define Num_LED 114

#define HEpin A0      //Hall Effect Sensor Pin
#define BuzzerPin A1  //Buzzer Pin

#define Color_ArrivalTime 0xff0000
#define Color_MeetingTime 0xff4400
#define Color_StoryTime 0xffff00
#define Color_ActivityTime 0x00ff00
#define Color_IndoorOutdoorTime 0x0000ff
#define Color_NapTime 0x0077ff
#define Color_CircleTime 0xff00ff
#define Color_GoodbyeTime 0x6600ff

const int stepsPerRevolution = 200;
const int stepSPEED = 60;
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

CRGB leds[Num_LED];

LEDdriver LEDseg;

int stepCount = 0;  // number of steps the motor has taken

void setup() {
  Serial.begin(115200);
  Serial.println("Transition Clock Prompter \nSYSTEM STARTING...");
  //myStepper.step(stepsPerRevolution);
  delay(1000);

  interrupt_setup();

  LEDseg.begin(8, 9, 10);
  LEDseg.printByte(188);
  LEDseg.printByte(188);
  LEDseg.latchData();




  FastLED.addLeds<WS2812, LED_DataPin, RGB>(leds, Num_LED);
  FastLED.setBrightness(95);
  FastLED.clear();
  FastLED.show();


  NeoRain_ArrivalTime(Color_ArrivalTime);
  NeoRain_MeetingTime(Color_MeetingTime);
  NeoRain_StoryTime(Color_StoryTime);
  NeoRain_ActivityTime(Color_ActivityTime);
  NeoRain_IndoorOutdoorTime(Color_IndoorOutdoorTime);
  NeoRain_NapTime(Color_NapTime);
  NeoRain_CircleTime(Color_CircleTime);
  NeoRain_GoodbyeTime(Color_GoodbyeTime);
  delay(1000);


  FastLED.clear();
  FastLED.show();


  pinMode(HEpin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  Buzz(1000);

  CalibrationMode = true;
  ArrowHand_Calibrate();
  CalibrationMode = false;
  LEDseg.printByte(15);
  LEDseg.printOneDigit(100);
  LEDseg.printOneDigit(100);
  LEDseg.latchData();

  promptTime_initialize();

  currentPT_Minute = pTime_Minute[p_ArrivalTime];
  currentPT_Second = pTime_Second[p_ArrivalTime];
  CurrentPT_Started = true;

  Serial.println("currentPT_Minute: " + String(currentPT_Minute));
  Serial.println("currentPT_Second: " + String(currentPT_Second));
  myStepper.setSpeed(stepSPEED);
  for (int i = 0; i < 11; i++) {
    myStepper.step(1);
  }

  NeoRain_ArrivalTime(Color_ArrivalTime);
}

void loop() {
  //myStepper.step(stepsPerRevolution);
  display_CurrentPromptTime();
  if (step_counter >= 10) {
    myStepper.step(1);
    step_counter = 0;
  }
}


void ArrowHand_Calibrate() {
  myStepper.setSpeed(stepSPEED);
  last_millis = millis();

  while (digitalRead(HEpin)) {
    myStepper.step(1);
    Serial.print("steps:");
    Serial.println(stepCount);
    stepCount++;
    //Serial.println("IR Sensor:" + String(digitalRead(HEpin)));
    LEDseg_Calibration();
  }

  Serial.println("Time Elapsed:" + String(millis() - last_millis));
  Serial.println("STEPPER & NeoPixel Test");
  FastLED.clear();
  FastLED.show();
}

void Buzz(uint32_t buzzDelay) {
  digitalWrite(BuzzerPin, 1);
  delay(buzzDelay);
  digitalWrite(BuzzerPin, 0);
}
