/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#include "motor.h"
#include "motor_state.h"

uint8_t cur_motor_state;

uint8_t motor_get_state(void) {
	return cur_motor_state;
}

uint8_t motor_get_winding_state(uint8_t winding, uint8_t state) {
	return state & (0x3 << (winding << 1));
}

void motor_set_state(uint8_t state) {
	// Set winding states
	uint8_t i;
	for(i = 0;i < 3;i++)
		motor_set_winding_state(i, motor_get_winding_state(i, state));
}

void motor_set_winding_state(uint8_t winding, uint8_t state) {
	// Check for change in winding's current state and pause for
	// MOSFET transition if needed
	// TODO

	// Set pin to correct state
	switch((winding << 2) | state) {
		// Winding A
		// State FLOAT
		case (MOTOR_WINDING_A << 2) | MOTOR_WINDING_STATE_FLOAT:
			PORTD |= (1<<PD2);
			PORTB |= (1<<PB2);
			break;
		// State POSITIVE
		case (MOTOR_WINDING_A << 2) | MOTOR_WINDING_STATE_POS:
			PORTD &= ~(1<<PD2);
			PORTB |= (1<<PB2);
			break;
		// State Negative
		case (MOTOR_WINDING_A << 2) | MOTOR_WINDING_STATE_NEG:
			PORTD |= (1<<PD2);
			PORTB &= ~(1<<PB2);
			break;
		// Winding B
		// State FLOAT
		case (MOTOR_WINDING_B << 2) | MOTOR_WINDING_STATE_FLOAT:
			PORTD |= (1<<PD3);
			PORTD |= (1<<PD4);
			break;
		// State POSITIVE
		case (MOTOR_WINDING_B << 2) | MOTOR_WINDING_STATE_POS:
			PORTD &= ~(1<<PD3);
			PORTD |= (1<<PD4);
			break;
		// State NEGATIVE
		case (MOTOR_WINDING_B << 2) | MOTOR_WINDING_STATE_NEG:
			PORTD |= (1<<PD3);
			PORTD &= ~(1<<PD4);
			break;
		// Winding C
		// State FLOAT
		case (MOTOR_WINDING_C << 2) | MOTOR_WINDING_STATE_FLOAT:
			PORTD |= (1<<PD5);
			PORTB |= (1<<PB0);
			break;
		// State POSITIVE
		case (MOTOR_WINDING_C << 2) | MOTOR_WINDING_STATE_POS:
			PORTD &= ~(1<<PD5);
			PORTB |= (1<<PB0);
			break;
		// State NEGATIVE
		case (MOTOR_WINDING_C << 2) | MOTOR_WINDING_STATE_NEG:
			PORTD |= (1<<PD5);
			PORTB &= ~(1<<PB0);
			break;
	}

	// Set winding state in cur_motor_state
	cur_motor_state &= ~(0x3 << (winding << 1)); 
	cur_motor_state |= state << (winding << 1);
}

void motor_init(void) {
	// Turn off all motor windings
	motor_set_state(motor_state_create(MOTOR_WINDING_STATE_FLOAT,
	                                   MOTOR_WINDING_STATE_FLOAT,
	                                   MOTOR_WINDING_STATE_FLOAT));

	// Set winding state select pins to output
	DDRD |= (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5);
	DDRB |= (1<<PB0) | (1<<PB2);
}

