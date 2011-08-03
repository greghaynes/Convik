#include "acmp.h"

void acmp_init(void) {
	// Comparator interrupt enable
	ACSR |= (1<<ACIE);

	// Set interrupt mode (on output falling edge)
	ACSR |= (1<<ACIS1);
	ACSR &= ~(1<<ACIS0);
}

