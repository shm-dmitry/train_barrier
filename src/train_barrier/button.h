#ifndef BUTTON_H_
#define BUTTON_H_

#include "stdint.h"

void button_init();
bool is_button_pressed(uint32_t ms);

#endif /* BUTTON_H_ */
