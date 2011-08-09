/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#include "pwm.h"

void pwm_init(void) {
	// Set PWM pin to output
	DDRB |= (1 << PB1);

	// Set Frequency
	ICR1 = 500;

	// Set default PWM duty cycle
	OCR1AL = 0;
	OCR1AH = 0;

	// Set clockdiv to 1
	TCCR1B |= (1 << CS10);

	// Set WGM11 and WGM13 to 1 for phase correct with IRC1 for TOP
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13);

	// Set COM1x1 to 1 and COM1x0 to 0 for phase correct pwm
	TCCR1A = (1 << COM1A1) | (1 << COM1B1);
}

void pwm_set(uint16_t val) {
	OCR1A = val;
}

