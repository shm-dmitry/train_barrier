#include "leds.h"
#include "Arduino.h"

#define LED_PIN         PB3
#define LED_LIGTH_CLOSED_PERIOD  1000
#define LED_LIGTH_OPENED_PERIOD  100

uint32_t next_time = 0;

void leds_init() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void leds_on_main_loop(uint32_t ms, bool closed) {
  if (ms > next_time) {
    digitalWrite(LED_PIN, digitalRead(LED_PIN) ? LOW : HIGH);
    if (closed) {
      next_time = ms + LED_LIGTH_CLOSED_PERIOD;
    } else {
      next_time = ms + LED_LIGTH_OPENED_PERIOD;
    }
  }
}
