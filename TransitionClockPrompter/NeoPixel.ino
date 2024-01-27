void Neo_ArrivalTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i] = CRGB(ColorValue);
  }
}

void Neo_MeetingTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i + 14] = CRGB(ColorValue);
  }
}

void Neo_StoryTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i + 28] = CRGB(ColorValue);
  }
}

void Neo_ActivityTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i + 42] = CRGB(ColorValue);
  }
}

void Neo_IndoorOutdoorTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i + 56] = CRGB(ColorValue);
  }
}

void Neo_NapTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i + 70] = CRGB(ColorValue);
  }
}

void Neo_CircleTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i + 85] = CRGB(ColorValue);
  }
}

void Neo_GoodbyeTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i + 100] = CRGB(ColorValue);
  }
}



void NeoRain_ArrivalTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}

void NeoRain_MeetingTime(uint32_t ColorValue) {
  for (int i = 14; i > 0; i--) {
    leds[i + 13] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}

void NeoRain_StoryTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i+28] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}

void NeoRain_ActivityTime(uint32_t ColorValue) {
  for (int i = 14; i > 0; i--) {
    leds[i + 41] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}

void NeoRain_IndoorOutdoorTime(uint32_t ColorValue) {
  for (int i = 0; i < 14; i++) {
    leds[i+56] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}

void NeoRain_NapTime(uint32_t ColorValue) {
  for (int i = 14; i > 0; i--) {
    leds[i + 70] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}

void NeoRain_CircleTime(uint32_t ColorValue) {
  for (int i = 0; i <= 14; i++) {
    leds[i+85] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}

void NeoRain_GoodbyeTime(uint32_t ColorValue) {
  for (int i = 14; i > 0; i--) {
    leds[i + 99] = CRGB(ColorValue);
    FastLED.show();
    delay(30);
  }
}