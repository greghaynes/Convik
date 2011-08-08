#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

enum motor_winding_t {
	MOTOR_WINDING_A = 0,
	MOTOR_WINDING_B = 1,
	MOTOR_WINDING_C = 2
};

void motor_set_state(uint8_t state);

void motor_set_winding_state(uint8_t winding, uint8_t state);


uint8_t motor_get_winding_state(uint8_t winding, uint8_t state);

uint8_t motor_get_state(void);

void motor_init(void);

#endif

