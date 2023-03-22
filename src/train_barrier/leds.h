#ifndef LEDS_H_
#define LEDS_H_

#include "stdint.h"

void leds_init();
void leds_on_main_loop(uint32_t ms, bool closed);

#endif /* LEDS_H_ */
