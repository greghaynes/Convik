/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#ifndef CONVIK_ADC_H
#define CONVIK_ADC_H

#include <avr/io.h>

/* Automatically enables ADC, no need to call adc_enable */
void adc_init(void);

/* Enables the ADC */
void adc_enable(void);

/* Disables the ADC */
void adc_disable(void);

#endif

