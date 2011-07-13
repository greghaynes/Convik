/* Taken from http://paul.graysonfamily.org/thoughts/avrlinux/ */

#define F_CPU 10000000UL

#include "core/pwm.h"

#include <avr/io.h>
#include <util/delay.h>

void delayms(uint16_t millis) {
	while ( millis ) {
		_delay_ms(1);
		millis--;
	}
}

int main(void) {
	DDRB |= 1<<PB0;
	pwm_init();
	pwm_set(0);

	uint16_t val = 0;

	while(1) {
		while(val < 500) {
			val++;
			pwm_set(val);
			delayms(1);
		}
		while(val > 0) {
			val--;
			pwm_set(val);
			delayms(1);
		}	
	}
	return 0;
}

