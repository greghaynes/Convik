#include "pwm.h"

#include <avr/io.h>

void pwm_init(void) {
	TCCR1A |= (1 << COM1A1);
}

