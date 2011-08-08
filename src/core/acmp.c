#include "acmp.h"

static acmp_handler _acmp_handler;

void acmp_init(void) {
	// Comparator interrupt enable
	ACSR |= (1<<ACIE);

	// Set interrupt mode (on output falling edge)
	ACSR |= (1<<ACIS1);
	ACSR &= ~(1<<ACIS0);
}

void acmp_set_handler(acmp_handler handler) {
	_acmp_handler = handler;
}

