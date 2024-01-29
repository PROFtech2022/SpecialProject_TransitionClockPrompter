
uint8_t LEDseg_CalibrationCounter = 0;
void LEDseg_Calibration() {
  if (!LEDseg_CalibToggle) {
    Serial.println("LEDseg Calib Toggle:" + String(LEDseg_CalibrationCounter));
    switch (LEDseg_CalibrationCounter) {
      case 0:
        LEDseg.printByte(188);
        LEDseg.printByte(188);
        LEDseg.latchData();
        break;
      case 1:  //seg A
        LEDseg.regData(0b01111110);
        LEDseg.regData(0b01111110);
        LEDseg.regData(0b01111110);
        LEDseg.regData(0b01111110);
        LEDseg.latchData();
        Neo_ArrivalTime(Color_ArrivalTime);
        Neo_MeetingTime(Color_MeetingTime);
        Neo_StoryTime(Color_StoryTime);
        Neo_ActivityTime(Color_ActivityTime);
        Neo_IndoorOutdoorTime(Color_IndoorOutdoorTime);
        Neo_NapTime(Color_NapTime);
        Neo_CircleTime(Color_CircleTime);
        Neo_GoodbyeTime(Color_GoodbyeTime);
        FastLED.show();
        break;
      case 2:  //seg B
        LEDseg.regData(0b10111110);
        LEDseg.regData(0b10111110);
        LEDseg.regData(0b10111110);
        LEDseg.regData(0b10111110);
        LEDseg.latchData();
        Neo_ArrivalTime(Color_GoodbyeTime);
        Neo_MeetingTime(Color_ArrivalTime);
        Neo_StoryTime(Color_MeetingTime);
        Neo_ActivityTime(Color_StoryTime);
        Neo_IndoorOutdoorTime(Color_ActivityTime);
        Neo_NapTime(Color_IndoorOutdoorTime);
        Neo_CircleTime(Color_NapTime);
        Neo_GoodbyeTime(Color_CircleTime);
        FastLED.show();
        break;
      case 3:  //seg C
        LEDseg.regData(0b11011110);
        LEDseg.regData(0b11011110);
        LEDseg.regData(0b11011110);
        LEDseg.regData(0b11011110);
        LEDseg.latchData();
        Neo_ArrivalTime(Color_CircleTime);
        Neo_MeetingTime(Color_GoodbyeTime);
        Neo_StoryTime(Color_ArrivalTime);
        Neo_ActivityTime(Color_MeetingTime);
        Neo_IndoorOutdoorTime(Color_StoryTime);
        Neo_NapTime(Color_ActivityTime);
        Neo_CircleTime(Color_IndoorOutdoorTime);
        Neo_GoodbyeTime(Color_NapTime);
        FastLED.show();
        break;
      case 4:  //seg D
        LEDseg.regData(0b11101110);
        LEDseg.regData(0b11101110);
        LEDseg.regData(0b11101110);
        LEDseg.regData(0b11101110);
        LEDseg.latchData();
        Neo_ArrivalTime(Color_NapTime);
        Neo_MeetingTime(Color_CircleTime);
        Neo_StoryTime(Color_GoodbyeTime);
        Neo_ActivityTime(Color_ArrivalTime);
        Neo_IndoorOutdoorTime(Color_MeetingTime);
        Neo_NapTime(Color_StoryTime);
        Neo_CircleTime(Color_ActivityTime);
        Neo_GoodbyeTime(Color_IndoorOutdoorTime);
        FastLED.show();
        break;
      case 5:  //seg E
        LEDseg.regData(0b11110110);
        LEDseg.regData(0b11110110);
        LEDseg.regData(0b11110110);
        LEDseg.regData(0b11110110);
        LEDseg.latchData();
        Neo_ArrivalTime(Color_IndoorOutdoorTime);
        Neo_MeetingTime(Color_NapTime);
        Neo_StoryTime(Color_CircleTime);
        Neo_ActivityTime(Color_GoodbyeTime);
        Neo_IndoorOutdoorTime(Color_ArrivalTime);
        Neo_NapTime(Color_MeetingTime);
        Neo_CircleTime(Color_StoryTime);
        Neo_GoodbyeTime(Color_ActivityTime);
        FastLED.show();
        break;
      case 6:  //seg F
        LEDseg.regData(0b11111010);
        LEDseg.regData(0b11111010);
        LEDseg.regData(0b11111010);
        LEDseg.regData(0b11111010);
        LEDseg.latchData();
        Neo_ArrivalTime(Color_ActivityTime);
        Neo_MeetingTime(Color_IndoorOutdoorTime);
        Neo_StoryTime(Color_NapTime);
        Neo_ActivityTime(Color_CircleTime);
        Neo_IndoorOutdoorTime(Color_GoodbyeTime);
        Neo_NapTime(Color_ArrivalTime);
        Neo_CircleTime(Color_MeetingTime);
        Neo_GoodbyeTime(Color_StoryTime);
        FastLED.show();
        break;
      case 7:  //seg F
        LEDseg.regData(0b11111100);
        LEDseg.regData(0b11111100);
        LEDseg.regData(0b11111100);
        LEDseg.regData(0b11111100);
        LEDseg.latchData();
        Neo_ArrivalTime(Color_StoryTime);
        Neo_MeetingTime(Color_ActivityTime);
        Neo_StoryTime(Color_IndoorOutdoorTime);
        Neo_ActivityTime(Color_NapTime);
        Neo_IndoorOutdoorTime(Color_CircleTime);
        Neo_NapTime(Color_GoodbyeTime);
        Neo_CircleTime(Color_ArrivalTime);
        Neo_GoodbyeTime(Color_MeetingTime);
        FastLED.show();
        break;
      default:
        LEDseg_CalibrationCounter = 0;
        Neo_ArrivalTime(Color_MeetingTime);
        Neo_MeetingTime(Color_StoryTime);
        Neo_StoryTime(Color_ActivityTime);
        Neo_ActivityTime(Color_IndoorOutdoorTime);
        Neo_IndoorOutdoorTime(Color_NapTime);
        Neo_NapTime(Color_CircleTime);
        Neo_CircleTime(Color_GoodbyeTime);
        Neo_GoodbyeTime(Color_ArrivalTime);
        FastLED.show();
        break;
    }
    LEDseg_CalibToggle = true;
  }
}