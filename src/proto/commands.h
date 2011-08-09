/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#ifndef CONVIK_COMMANDS_H
#define CONVIK_COMMANDS_H

#include <avr/io.h>

struct command_info {
	uint8_t args_length;
	void (*handler)(char *args, uint8_t length);
};

void commands_init(void);

struct command_info *command_get(uint8_t id);

void command_run(uint8_t id, char *args, uint8_t arglen);

#endif

