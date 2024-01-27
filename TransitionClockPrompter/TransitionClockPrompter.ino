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

#define LED_DataPin 7
#define Num_LED 114

#define HEpin A0  //Hall Effect Sensor Pin

const int stepsPerRevolution = 32;

Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

CRGB leds[Num_LED];

uint32_t last_millis = 0;

#define Color_ArrivalTime 0xff0000
#define Color_MeetingTime 0xff4400
#define Color_StoryTime 0xffff00
#define Color_ActivityTime 0x00ff00
#define Color_IndoorOutdoorTime 0x0000ff
#define Color_NapTime 0x0077ff
#define Color_CircleTime 0xff00ff
#define Color_GoodbyeTime 0x6600ff

void setup() {
  Serial.begin(115200);
  Serial.println("Transition Clock Prompter \nSYSTEM STARTING...");
  //myStepper.step(stepsPerRevolution);
  delay(1000);

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
  ArrowHand_Calibrate();
}

void loop() {
  //myStepper.step(stepsPerRevolution);
}


void ArrowHand_Calibrate() {
  myStepper.setSpeed(60);
  last_millis = millis();
  while (digitalRead(HEpin)) {
    myStepper.step(stepsPerRevolution);
    Serial.println("Hall Effect:" + String(digitalRead(HEpin)));
  }
  myStepper.step(stepsPerRevolution);
  delay(2000);
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
  delay(2000);
  FastLED.clear();
  FastLED.show();
  Serial.println("Time Elapsed:" + String(millis() - last_millis));
}
