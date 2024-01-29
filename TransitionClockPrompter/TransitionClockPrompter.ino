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

const int stepsPerRevolution = 32;
const int stepSPEED=60;
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

CRGB leds[Num_LED];

LEDdriver LEDseg;

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
  FastLED.setBrightness(90);
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
  NeoRain_ArrivalTime(Color_ArrivalTime);
}

void loop() {
  //myStepper.step(stepsPerRevolution);
  display_CurrentPromptTime();
  if(step_counter>=200){
      myStepper.step(stepsPerRevolution);
      delay(250);
      step_counter=0;
  }

}


void ArrowHand_Calibrate() {
  myStepper.setSpeed(stepSPEED);
  last_millis = millis();
  while (digitalRead(HEpin)) {
    if (!digitalRead(HEpin)) {
      goto alignExit;
    }
    myStepper.step(stepsPerRevolution);
    //Serial.println("IR Sensor:" + String(digitalRead(HEpin)));
    LEDseg_Calibration();
  }
alignExit:
  Serial.println("Time Elapsed:" + String(millis() - last_millis));

  FastLED.clear();
  Neo_ArrivalTime(Color_ArrivalTime);
  FastLED.show();

  Serial.println("STEPPER & NeoPixel Test");

  uint32_t millis_diff;
  last_millis = millis();

  while (digitalRead(HEpin)) {
    myStepper.step(stepsPerRevolution);
    Serial.println("TE:" + String(millis() - last_millis));
    millis_diff = millis() - last_millis;
    if (millis_diff > 4500 && millis_diff < 11800) {
      FastLED.clear();
      Neo_MeetingTime(Color_MeetingTime);
      FastLED.show();
    } else if (millis_diff > 11800 && millis_diff < 19500) {
      FastLED.clear();
      Neo_StoryTime(Color_StoryTime);
      FastLED.show();
    } else if (millis_diff > 19500 && millis_diff < 33000) {
      FastLED.clear();
      Neo_ActivityTime(Color_ActivityTime);
      FastLED.show();
    } else if (millis_diff > 33000 && millis_diff < 41000) {
      FastLED.clear();
      Neo_IndoorOutdoorTime(Color_IndoorOutdoorTime);
      FastLED.show();
    } else if (millis_diff > 41000 && millis_diff < 53000) {
      FastLED.clear();
      Neo_NapTime(Color_NapTime);
      FastLED.show();
    } else if (millis_diff > 53000 && millis_diff < 60000) {
      FastLED.clear();
      Neo_CircleTime(Color_CircleTime);
      FastLED.show();
    } else if (millis_diff > 60000) {
      FastLED.clear();
      Neo_GoodbyeTime(Color_GoodbyeTime);
      FastLED.show();
    }
  }
  myStepper.step(stepsPerRevolution);
  delay(100);
  FastLED.clear();
  FastLED.show();
  Serial.println("Time Elapsed:" + String(millis() - last_millis));
}
