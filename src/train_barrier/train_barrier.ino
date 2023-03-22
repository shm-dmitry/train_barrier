#include "noise.h"
#include "servo.h"
#include "leds.h"
#include "button.h"

#define NOINPUT_AUTO_OPEN_DELAY 20000
#define NOINPUT_POWERDOWN_DELAY (NOINPUT_AUTO_OPEN_DELAY + 5000)

uint32_t lastactivity = 0;

void setup() {
  leds_init();
  servo_init();
  noise_init();
  button_init();
}

void loop() {
  uint32_t ms = millis();
  
  if (is_button_pressed(ms)) {
    servo_close_open_invert(ms);
    lastactivity = ms;
  }

  if (ms > lastactivity + NOINPUT_AUTO_OPEN_DELAY) {
    servo_open_now(ms);
  }

  bool closed = servo_is_closed();

  leds_on_main_loop(ms, closed);
  noise_on_main_loop(ms, closed);
  servo_on_main_loop(ms);

  if (ms > lastactivity + NOINPUT_POWERDOWN_DELAY) {
    servo_disable();
    noise_stop();
    while(true) { }; // schematics will power down us few seconds later
  }
}
