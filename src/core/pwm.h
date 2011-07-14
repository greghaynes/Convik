#ifndef CONVIK_PWM_H
#define CONVIK_PWM_H

#include <avr/io.h>

void pwm_init(void);
void pwm_set(uint16_t val);

#endif

