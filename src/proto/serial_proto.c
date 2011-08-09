/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#include "serial_proto.h"
#include "commands.h"
#include "../utils/char_buffer.h"

#define SERIAL_PROTO_BUFF_SIZE 9

// Buffer for proto data
static struct char_buffer serial_buffer;
static char serial_buffer_data[SERIAL_PROTO_BUFF_SIZE];

void serial_proto_init(void) {
	// Initialize char buffer
	char_buffer_init(&serial_buffer, serial_buffer_data, SERIAL_PROTO_BUFF_SIZE);
}


void serial_proto_reset(void) {
	// Reset the char buffer
	char_buffer_reset(&serial_buffer);
}

// Get command stuct for current buffer
// Returns 0 for invalid command
struct command_info *serial_proto_cmd_info(void) {
	return command_get((uint8_t)serial_buffer.data[0]);
}

// Returns serial proto length of cmd
uint8_t serial_proto_cmd_length(struct command_info *cmd) {
	return cmd->args_length + 3; // ID (1) + args + CR(1) + LF(1)
}

void serial_proto_got_char(char ch) {
	// Each time we get a char we perform the following:
	// Append the char to the buffer
	// Check that we have a valid command in the buffer
	//  * Since the first byte is cmd_id it should always be valid at this
	//  * stage.
	//  * If command is not valid reset buffer and return.
	// If we have a full command in buffer:
	//  * Check end CR + LF
	//  * * If invalid then reset
	//  * Run command handler

	// Append char to current buffer and increment buff ndx
	char_buffer_append(&serial_buffer, &ch, 1);

	// Check to see if we got a full command
	struct command_info *cmd = serial_proto_cmd_info();
	if(!cmd) {
		// Invalid command, reset buffer
		serial_proto_reset();
		return;
	}

	// Length of command in buffer when completed
	uint8_t cmd_len = serial_proto_cmd_length(cmd);
	uint8_t buff_len = char_buffer_length(&serial_buffer);

	// If we have a complete command in the buffer
	if(buff_len == cmd_len) {
		// Verify end tag
		if(serial_buffer.data[buff_len-2] != '\r' ||
		   serial_buffer.data[buff_len-2] != '\n') {
			// Invalid end tag
			// Reset and return
			serial_proto_reset();
			return;
		}

		// Null out start of end tag so args end in '\0'
		serial_buffer.data[buff_len-2] = '\0';

		// Run command
		command_run((uint8_t)serial_buffer.data[0], serial_buffer.data+1, buff_len-3);

		// Reset
		serial_proto_reset();
	}
}

