#include "commands.h"

void command_motor_set_throttle(char *args, uint8_t length);
void command_motor_get_throttle(char *args, uint8_t length);

static struct command_info commands[] = {
	/* 0: Set throttle */
	{ 4, command_motor_set_throttle },
	/* 1: Get throttle */
	{ 3, command_motor_get_throttle },
	/* Invalid, end of commands vector (Dont remove) */
	{ 0, 0 }
};

static uint8_t command_cnt;

void command_motor_set_throttle(char *args, uint8_t length) {
}

void command_motor_get_throttle(char *args, uint8_t length) {
}

void commands_init(void) {
	// Determine command_cnt
	for(command_cnt=0;commands[command_cnt].args_length != 0 || commands[command_cnt].handler != 0;command_cnt++);
}

struct command_info *command_get(uint8_t id) {
	if(id >= command_cnt)
		return 0;
	return &commands[id];
}

void command_run(uint8_t id, char *args, uint8_t arglen) {
	command_get(id)->handler(args, arglen);
}

