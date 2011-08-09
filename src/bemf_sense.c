#include "bemf_sense.h"
#include "core/acmp.h"

void bemf_sense_init(void) {
	acmp_init();

	DDRC |= (1<<DDC0) | (1<<DDC1);
	PORTC &= ~((1<<PORTC0) | (1<<PORTC1));
}

void bemf_sense_set_winding(uint8_t winding) {
	switch(winding) {
		case MOTOR_WINDING_A:
			// PC0 = 0, PC1 = 0
			PORTC &= ~((1<<PORTC0) | (1<<PORTC1));
			break;
		case MOTOR_WINDING_B:
			// PC0 = 1, PC1 = 0
			PORTC = (PORTC & ~(1<<PORTC1)) | (1<<PORTC0);
			break;
		case MOTOR_WINDING_C:
			// PC0 = 1, PC1 = 1
			PORTC |= (1<<PORTC0) | (1<<PORTC1);
			break;
	}
}

