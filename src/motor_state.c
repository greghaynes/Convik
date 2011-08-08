#include "motor_state.h"
#include "motor.h"

// Sequence of states (A, B, C, Sense)
static uint8_t motor_state_seq[6][4] = {
	{
		MOTOR_WINDING_STATE_FLOAT, // A
		MOTOR_WINDING_STATE_POS, // B
		MOTOR_WINDING_STATE_NEG, // C
		MOTOR_WINDING_A // Sense Winding
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


uint8_t motor_state_next(void) {
	return 0;
}

