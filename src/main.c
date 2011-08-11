/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#include "config.h"
#include "core/pwm.h"
#include "core/usart.h"
#include "utils/char_fifo.h"

#include <avr/io.h>
#include <util/delay.h>

void delayms(uint16_t millis) {
	while ( millis ) {
		_delay_ms(1);
		millis--;
	}
}

static uint8_t state;

void all_off(void) {
	PORTB &= ~((1<<PB0) | (1<<PB1) | (1<<PB2));
	PORTC &= ~(1<<PC0);
	PORTD &= ~((1<<PD6) | (1<<PD7));
}

void next_state(void) {
	if(state >= 5)
		state = 0;
	else
		++state;

	all_off();
	switch(state) {
		case 0:
			PORTB |= (1<<PB2);
			PORTD |= (1<<PD6);
			break;
		case 1:
			PORTC |= (1<<PC0);
			PORTD |= (1<<PD6);
			break;
		case 2:
			PORTC |= (1<<PC0);
			PORTD |= (1<<PD7);
			break;
		case 3:
			PORTD |= (1<<PD7);
			PORTB |= (1<<PB1);
			break;
		case 4:
			PORTB |= (1<<PB1);
			PORTB |= (1<<PB0);
			break;
		case 5:
			PORTB |= (1<<PB2);
			PORTB |= (1<<PB0);
			break;
	}
}

int main(void) {
	DDRB = (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	DDRC = (1<<DDC0);
	DDRD = (1<<DDD6) | (1<<DDD7);

	adc_init();
	DIDR0 |= (1<<ADC1D);
	uint8_t adc_val;

	while(1) {
		next_state();
		// start ADC
		ADCSRA |= (1<<ADSC);
		// Wait for ADC Complete
		while(ADCSRA & (1<<ADSC));
		adc_val = ADCH;
		
		delayms(adc_val);
	}
	return 0;
}

