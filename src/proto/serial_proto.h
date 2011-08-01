#ifndef CONVIK_SERIAL_PROTO_H
#define CONVIK_SERIAL_PROTO_H

#include <avr/io.h>

/* Call before using any serial_proto methods */
void serial_proto_init(void);

/* Reset state and buffers to initial condition */
void serial_proto_reset(void);

/* Update state based on new char input.
 * Called for each char received. This then calls command handlers
 * and updates proto state. */
void serial_proto_got_char(char ch);

#endif

