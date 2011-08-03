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
	usart_init();
	pwm_init();
	pwm_set(0);

	while(1) {
		if(char_fifo_is_empty(usart_recv_fifo()))
			usart_send_char(char_fifo_pop(usart_recv_fifo()));
	}
	return 0;
}

