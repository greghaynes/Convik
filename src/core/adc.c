/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#include "adc.h"

void adc_init(void) {
	// Enable ADC, set prescaler to 4
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	// ADC Mux
	ADMUX = (1<<ADLAR) | (1<<MUX0);

}

