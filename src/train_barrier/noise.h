#ifndef NOISE_H_
#define NOISE_H_

#include "stdint.h"

void noise_init();
void noise_on_main_loop(uint32_t ms, bool closed);
void noise_stop();

#endif /* NOISE_H_ */
