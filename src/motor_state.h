/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#ifndef CONVIK_MOTOR_STATE_H
#define CONVIK_MOTOR_STATE_H

/* Code which controls the sequential stepping between motor states
 * for use during open loop startup and closed loop */

#include <avr/io.h>

enum motor_winding_state_t {
	MOTOR_WINDING_STATE_FLOAT = 0,
	MOTOR_WINDING_STATE_POS = 1,
	MOTOR_WINDING_STATE_NEG = 2
};

/* Call to set state 0 */
void motor_state_start(void);

/* Create a uint8_t representing the states of all three coils */
uint8_t motor_state_create(uint8_t a,
                           uint8_t b,
                           uint8_t c);

/* Advance the motor windings to the next state */
void motor_state_next(void);

#endif

