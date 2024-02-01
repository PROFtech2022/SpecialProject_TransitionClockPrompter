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

  /*
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TIMSK1 |= (1 << OCIE1A);
  */

  sei();  //enable all interrupts
}

/*
//Interrupt Timer1 1HZ
ISR(TIMER1_COMPA_vect){
    cli();
  if (CalibrationMode) {
      LEDseg_CalibrationCounter++;
      LEDseg_CalibToggle = false;
  }
    sei();
        LEDseg_Calibration();
}
*/

ISR(TIMER2_COMPA_vect) {
  cli();

  if (digitalRead(HEpin)) {
    arrow90Detected = true;
  }

  if (CalibrationMode) {
    LEDseg_IntCounter++;

    if (LEDseg_IntCounter >= 4000) {
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
    }

    arrowHeadCounter++;
    if (arrowHeadCounter >= 4000) {
      step_counter++;
      arrowHeadCounter = 0;
    }
  }
  sei();
}