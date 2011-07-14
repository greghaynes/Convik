#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

enum motor_winding_t {
	MOTOR_WINDING_A = 0,
	MOTOR_WINDING_B = 1,
	MOTOR_WINDING_C = 2
};

enum motor_winding_state_t {
	MOTOR_WINDING_STATE_FLOAT = 0,
	MOTOR_WINDING_STATE_POS = 1,
	MOTOR_WINDING_STATE_NEG = 2
};

uint8_t motor_state_create(uint8_t a,
                           uint8_t b,
                           uint8_t c);

uint8_t motor_state_get_winding(uint8_t winding, uint8_t state);

void motor_state_set(uint8_t state);

void motor_winding_set(uint8_t winding, uint8_t state);

void motor_init(void);

#endif

