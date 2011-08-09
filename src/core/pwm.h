/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#ifndef CONVIK_PWM_H
#define CONVIK_PWM_H

#include <avr/io.h>

void pwm_init(void);
void pwm_set(uint16_t val);

#endif

