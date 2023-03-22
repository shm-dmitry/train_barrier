#include "noise.h"
#include "Arduino.h"
#include "servo.h"

#define NOISE_PIN   PB0

uint16_t noise_onoff = 0;
volatile uint8_t noise_off_counter = 0;

ISR(TIM0_COMPA_vect) {
  digitalWrite(NOISE_PIN, digitalRead(NOISE_PIN) ? LOW : HIGH);
  noise_off_counter--;
  if (noise_off_counter == 0) {
    TIMSK0 &= ~(_BV(OCIE0A));
  }
}

void noise_init() {
  pinMode(NOISE_PIN, OUTPUT);
  digitalWrite(NOISE_PIN, LOW);

  OCR0A = 1;
  TIMSK0 |= (1 << OCIE0A);
}

void noise_on_main_loop(uint32_t ms, bool closed) {
  if (ms > noise_onoff * 500) {
    noise_onoff++;
    if (noise_onoff % 2 == 0) {
      TIMSK0 &= ~(_BV(OCIE0A));
      digitalWrite(NOISE_PIN, LOW);
    } else {
      noise_off_counter = closed ? 0xFF : 0x02;
      TIMSK0 |= (1 << OCIE0A);
    }
  }
}

void noise_stop() {
  TIMSK0 &= ~(_BV(OCIE0A));
  digitalWrite(NOISE_PIN, LOW);
}
