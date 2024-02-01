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

  //promptTime_initialize();

  pt_currentPrompt = 0;
  currentPT_Minute = PT_getNewTime(p_Minute, pt_currentPrompt);
  currentPT_Second = PT_getNewTime(p_Second, pt_currentPrompt);
  CurrentPT_Started = true;

  Serial.println("currentPT_Minute: " + String(currentPT_Minute));
  Serial.println("currentPT_Second: " + String(currentPT_Second));
  myStepper.setSpeed(stepSPEED);
  for (int i = 0; i < 9; i++) {
    myStepper.step(1);
  }

  NeoRain_ArrivalTime(Color_ArrivalTime);
}

void loop() {
  //myStepper.step(stepsPerRevolution);
  display_CurrentPromptTime();


  if (pt_currentPrompt == p_ArrivalTime || pt_currentPrompt == p_IndoorOutdoorTime) {
    if (step_counter >= 10) {
      myStepper.step(1);
      step_counter = 0;
    }
  } else if (pt_currentPrompt == p_ActivityTime) {
    if (step_counter >= 8) {
      myStepper.step(1);
      step_counter = 0;
    }
  } else {
    if (step_counter >= 11) {
      myStepper.step(1);
      step_counter = 0;
    }
  }


  if (BuzzToggle) {
    getNewPrompt();
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

void getNewPrompt() {
  pt_currentPrompt++;

  currentPT_Minute = PT_getNewTime(p_Minute, pt_currentPrompt);
  currentPT_Second = PT_getNewTime(p_Second, pt_currentPrompt);
  CurrentPT_Started = true;
  BuzzToggle = false;


  if (currentPT_Minute < 10) {
    LEDseg.printNum(255);
    LEDseg.printNum(currentPT_Minute);
  } else {
    LEDseg.printNum(currentPT_Minute / 10);
    LEDseg.printNum(currentPT_Minute % 10);
  }


  LEDseg.printNum((currentPT_Second / 10) + 100);
  LEDseg.printNum((currentPT_Second % 10) + 100);

  LEDseg.latchData();

  FastLED.clear();
  FastLED.show();

  switch (pt_currentPrompt) {
    case p_ArrivalTime:
      NeoRain_ArrivalTime(Color_ArrivalTime);
      break;
    case p_MeetingTime:
      NeoRain_MeetingTime(Color_MeetingTime);
      break;
    case p_StoryTime:
      NeoRain_StoryTime(Color_StoryTime);
      break;
    case p_ActivityTime:
      NeoRain_ActivityTime(Color_ActivityTime);
      break;
    case p_IndoorOutdoorTime:
      NeoRain_IndoorOutdoorTime(Color_IndoorOutdoorTime);
      break;
    case p_NapTime:
      NeoRain_NapTime(Color_NapTime);
      break;
    case p_CircleTime:
      NeoRain_CircleTime(Color_CircleTime);
      break;
    case p_GoodbyeTime:
      NeoRain_GoodbyeTime(Color_GoodbyeTime);
      break;
    default:
      pt_currentPrompt = 0;
      break;
  }

  FastLED.show();

  for (int i = 0; i < 5; i++) {
    myStepper.step(1);
  }

  if (pt_currentPrompt == p_MeetingTime) {
    for (int i = 0; i < 15; i++) {
      myStepper.step(1);
    }
  } else if (pt_currentPrompt == p_StoryTime) {
    for (int i = 0; i < 20; i++) {
      myStepper.step(1);
    }
  } else if (pt_currentPrompt == p_ActivityTime) {
    for (int i = 0; i < 30; i++) {
      myStepper.step(1);
    }
  }

  delay(3000);
}