void interrupt_setup() {
  cli();  // disable interrupts

  // set timer2 interrupt at 8kHz
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 249;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS21);
  TIMSK2 |= (1 << OCIE2A);
  sei();  //enable all interrupts
}



ISR(TIMER2_COMPA_vect) {
  cli();
  if (CalibrationMode) {
    LEDseg_IntCounter++;

    if (LEDseg_IntCounter >= 8000) {
      LEDseg_CalibrationCounter++;
      LEDseg_IntCounter = 0;
      LEDseg_CalibToggle = false;
    }
  }


  if (CurrentPT_Started) {
    CurrentPT_IntCounter++;
    if (CurrentPT_IntCounter >= 8000) {
      CurrentPT_IntCounter = 0;
      currentPT_Second--;
      step_counter++;
    }
  }
  sei();
}