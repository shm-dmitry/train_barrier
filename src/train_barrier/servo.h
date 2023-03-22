#ifndef SERVO_H_
#define SERVO_H_

#include "stdint.h"

void servo_init();
void servo_on_main_loop(uint32_t ms);
void servo_close_open_invert(uint32_t ms);
void servo_disable();
void servo_open_now(uint32_t ms);
bool servo_is_closed();

#endif /* SERVO_H_ */
