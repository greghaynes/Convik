#include "config.h"
#include "core/pwm.h"
#include "core/usart.h"

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
			delayms(5);
		}
		usart_send_char('a');
		while(val > 0) {
			val--;
			pwm_set(val);
			delayms(5);
		}	
		usart_send_char('b');
	}
	return 0;
}

