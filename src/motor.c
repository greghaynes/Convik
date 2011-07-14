#include "motor.h"

static uint8_t cur_motor_state;

static uint8_t cur_motor_state_ndx;

static uint8_t motor_state_seq[6][4] = {
	{
		MOTOR_WINDING_STATE_FLOAT,
		MOTOR_WINDING_STATE_POS,
		MOTOR_WINDING_STATE_NEG,
		MOTOR_WINDING_A
	}, {
		MOTOR_WINDING_STATE_POS,
		MOTOR_WINDING_STATE_FLOAT,
		MOTOR_WINDING_STATE_NEG,
		MOTOR_WINDING_B
	}, {
		MOTOR_WINDING_STATE_POS,
		MOTOR_WINDING_STATE_NEG,
		MOTOR_WINDING_STATE_FLOAT,
		MOTOR_WINDING_C
	}, {
		MOTOR_WINDING_STATE_FLOAT,
		MOTOR_WINDING_STATE_NEG,
		MOTOR_WINDING_STATE_POS,
		MOTOR_WINDING_A
	}, {
		MOTOR_WINDING_STATE_NEG,
		MOTOR_WINDING_STATE_FLOAT,
		MOTOR_WINDING_STATE_POS,
		MOTOR_WINDING_B
	}, {
		MOTOR_WINDING_STATE_NEG,
		MOTOR_WINDING_STATE_POS,
		MOTOR_WINDING_STATE_FLOAT,
		MOTOR_WINDING_C
	} };

uint8_t motor_state_create(uint8_t a,
                           uint8_t b,
                           uint8_t c) {
	return a | (b << 2) | (c << 4);
}

uint8_t motor_state_get_winding(uint8_t winding, uint8_t state) {
	return state & (0x3 << (winding << 1));
}

void motor_state_set(uint8_t state) {
	// Set winding states
	uint8_t i;
	for(i = 0;i < 3;i++)
		motor_winding_set(i, motor_state_get_winding(i, state));
}

void motor_winding_set(uint8_t winding, uint8_t state) {
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
	motor_state_set(motor_state_create(MOTOR_WINDING_STATE_FLOAT,
	                                   MOTOR_WINDING_STATE_FLOAT,
	                                   MOTOR_WINDING_STATE_FLOAT));

	// Set winding state select pins to output
	DDRD |= (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5);
	DDRB |= (1<<PB0) | (1<<PB2);
}

uint8_t motor_state_next(void) {
	return 0;
}

