#include "button.h"
#include "Arduino.h"

#define BUTTON_PIN PB2
#define BUTTON_PRESS_DELAY 2000
#define BUTTON_FIRST_ACTION_DELAY 1000

uint32_t button_next_press_date = 0;

void button_init() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button_next_press_date = BUTTON_FIRST_ACTION_DELAY;
}

bool is_button_pressed(uint32_t ms) {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (ms < button_next_press_date) {
      return false;
    }

    button_next_press_date = ms + BUTTON_PRESS_DELAY;
    return true;
  }

  return false;
}
