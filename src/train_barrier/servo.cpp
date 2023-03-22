#include "servo.h"
#include "Arduino.h"

#define SERVO_CONTROL_PIN PB1
#define SERVO_PWR_ON_PIN  PB4

#define SERVO_CLOSE_PERIOD   20
#define SERVO_OPEN_PERIOD    10
#define SERVO_LOW_PERIOD     2000
#define SERVO_WORKING_PERIOD 400

uint8_t servo_high_period  = 0;
uint32_t servo_pulse_change = 0;
uint32_t servo_stop_after   = 0;

void servo_init() {
  pinMode(SERVO_CONTROL_PIN, OUTPUT);
  digitalWrite(SERVO_CONTROL_PIN, LOW);

  pinMode(SERVO_PWR_ON_PIN, OUTPUT);
  digitalWrite(SERVO_PWR_ON_PIN, LOW);

  servo_high_period  = SERVO_CLOSE_PERIOD;
  servo_stop_after   = SERVO_WORKING_PERIOD;
}

void servo_on_main_loop(uint32_t ms) {
  if (ms > servo_stop_after) {
    if (digitalRead(SERVO_CONTROL_PIN) == HIGH) {
      digitalWrite(SERVO_CONTROL_PIN, LOW);
    }
    return;
  }
  
  uint32_t now = micros();

  if (now > servo_pulse_change) {
    if (digitalRead(SERVO_CONTROL_PIN) == HIGH) {
      servo_pulse_change = now + (uint32_t) SERVO_LOW_PERIOD;
      digitalWrite(SERVO_CONTROL_PIN, LOW);
    } else {
      servo_pulse_change = now + (uint32_t) servo_high_period * (uint32_t) 100;
      digitalWrite(SERVO_CONTROL_PIN, HIGH);
    }
  }
}

void servo_close_open_invert(uint32_t ms) {
  servo_stop_after   = ms + SERVO_WORKING_PERIOD;
  servo_high_period  = (servo_high_period == SERVO_CLOSE_PERIOD) ? SERVO_OPEN_PERIOD : SERVO_CLOSE_PERIOD;
}

void servo_open_now(uint32_t ms) {
  if (servo_high_period == SERVO_CLOSE_PERIOD) {
    servo_close_open_invert(ms);
  }
}

bool servo_is_closed() {
  return servo_high_period == SERVO_CLOSE_PERIOD;
}

void servo_disable() {
  digitalWrite(SERVO_PWR_ON_PIN, HIGH);
  digitalWrite(SERVO_CONTROL_PIN, LOW);
}
