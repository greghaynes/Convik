/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#include "motor_state.h"
#include "motor.h"

static uint8_t cur_state_ndx;

#define MOTOR_STATE(a, b, c, s)  (a | (b << 2) | (c << 4) | (s << 6))

// Sequence of states (A, B, C, Sense)
static uint8_t motor_state_seq[6] = {
	MOTOR_STATE(MOTOR_WINDING_STATE_FLOAT, // A
	            MOTOR_WINDING_STATE_POS, // B
	            MOTOR_WINDING_STATE_NEG, // C
	            MOTOR_WINDING_A), // Sense Winding
	MOTOR_STATE(MOTOR_WINDING_STATE_POS,
	            MOTOR_WINDING_STATE_FLOAT,
	            MOTOR_WINDING_STATE_NEG,
	            MOTOR_WINDING_B),
	MOTOR_STATE(MOTOR_WINDING_STATE_POS,
	            MOTOR_WINDING_STATE_NEG,
	            MOTOR_WINDING_STATE_FLOAT,
	            MOTOR_WINDING_C),
	MOTOR_STATE(MOTOR_WINDING_STATE_FLOAT,
	            MOTOR_WINDING_STATE_NEG,
	            MOTOR_WINDING_STATE_POS,
	            MOTOR_WINDING_A),
	MOTOR_STATE(MOTOR_WINDING_STATE_NEG,
	            MOTOR_WINDING_STATE_FLOAT,
	            MOTOR_WINDING_STATE_POS,
	            MOTOR_WINDING_B),
	MOTOR_STATE(MOTOR_WINDING_STATE_NEG,
	            MOTOR_WINDING_STATE_POS,
	            MOTOR_WINDING_STATE_FLOAT,
	            MOTOR_WINDING_C)
};

void motor_state_start(void) {
	cur_state_ndx = 5;
	motor_state_next();
}

uint8_t motor_state_create(uint8_t a,
                           uint8_t b,
                           uint8_t c) {
	return MOTOR_STATE(a, b, c, 0);
}


void motor_state_next(void) {
	if(cur_state_ndx >= 5)
		cur_state_ndx = 0;
	else
		++cur_state_ndx;
	motor_set_state(motor_state_seq[cur_state_ndx]);
}

