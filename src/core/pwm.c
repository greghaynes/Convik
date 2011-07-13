#include "pwm.h"


void pwm_init(void) {
	// Set PWM pin to output
	DDRB |= (1 << PB1);

	// Set default PWM duty cycle
	OCR1AL = 0;
	OCR1AH = 0;

	// Set COM1x1 to 1 and COM1x0 to 0 for phase correct pwm
	TCCR1A = (1 << COM1A1) | (1 << COM1B1);

	// Set WGM11 and WGM13 to 1 for phase correct with 10 bit TOP
	TCCR1A |= (1 << WGM11) | (1 << WGM10);

	// Set clockdiv to 1
	TCCR1B |= (1 << CS10);
}

void pwm_set(uint8_t high, uint8_t low) {
	OCR1AH = high;
	OCR1AL = low;
}

