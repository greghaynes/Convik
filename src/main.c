/* Taken from http://paul.graysonfamily.org/thoughts/avrlinux/ */

#define F_CPU 10000000UL

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
	while(1) {
		PORTB &= ~(1<<PB0); /* LED on */
		delayms(100);
		PORTB |= 1<<PB0; /* LED off */
		delayms(100);
	}
	return 0;
}

