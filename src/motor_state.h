#ifndef CONVIK_MOTOR_STATE_H
#define CONVIK_MOTOR_STATE_H

#include <avr/io.h>

enum motor_winding_state_t {
	MOTOR_WINDING_STATE_FLOAT = 0,
	MOTOR_WINDING_STATE_POS = 1,
	MOTOR_WINDING_STATE_NEG = 2
};

uint8_t motor_state_create(uint8_t a,
                           uint8_t b,
                           uint8_t c);

uint8_t motor_state_next(void);

#endif

