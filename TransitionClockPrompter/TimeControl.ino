
void promptTime_initialize() {
  pTime_Minute[p_ArrivalTime] = 15;  // Arrival Time
  pTime_Second[p_ArrivalTime] = 0;   // Arrival Time

  pTime_Minute[p_MeetingTime] = 20;  // Meeting Time
  pTime_Second[p_MeetingTime] = 0;   // Meeting Time

  pTime_Minute[p_StoryTime] = 20;  // Story Time
  pTime_Second[p_StoryTime] = 0;   // Story Time

  pTime_Minute[p_ActivityTime] = 30;  // Activity Time
  pTime_Second[p_ActivityTime] = 0;   // Activity Time

  pTime_Minute[p_IndoorOutdoorTime] = 20;  // Indoor/Outdoor Time
  pTime_Second[p_IndoorOutdoorTime] = 0;   // Indoor/Outdoor Time

  pTime_Minute[p_NapTime] = 30;  // Nap Time
  pTime_Second[p_NapTime] = 0;   // Nap Time

  pTime_Minute[p_CircleTime] = 20;  // Circle Time
  pTime_Second[p_CircleTime] = 0;   // Circle Time

  pTime_Minute[p_GoodbyeTime] = 10;  // Goodbye Time
  pTime_Second[p_GoodbyeTime] = 0;   // Goodbye Time
}


void display_CurrentPromptTime() {
  PT_VariableControl();

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
}

void PT_VariableControl() {
  if (currentPT_Second > 60 && currentPT_Second < 255) {
    currentPT_Second = 0;
  } else if (currentPT_Second == 255) {
    currentPT_Second = 59;
    currentPT_Minute--;
  }

  if (currentPT_Minute == 0 && currentPT_Second == 0 && !BuzzToggle) {

    LEDseg.printNum(255);
    LEDseg.printNum(100);
    LEDseg.printNum(100);
    LEDseg.printNum(100);

    LEDseg.latchData();
    Buzz(3000);
    CurrentPT_Started = false;
    BuzzToggle = true;
  }
}