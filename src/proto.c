#include "proto.h"
#include "motor.h"

#define PROTO_BUFF_SIZE 9
#define PROTO_CMD_COUNT 3

void proto_cmd_motor_set_throttle(char *buff, uint8_t length);
void proto_cmd_motor_get_throttle(char *buff, uint8_t length);

struct proto_cmd_info {
	uint8_t length;
	void (*handler)(char *buff, uint8_t length);
};

// Commands
static struct proto_cmd_info proto_commands[PROTO_CMD_COUNT] = {
	{ 0, 0 }, // Invalid
	{ 4, proto_cmd_motor_set_throttle }, // Set throttle
	{ 3, proto_cmd_motor_get_throttle }, // Get throttle
};

static char proto_buff[PROTO_BUFF_SIZE];

// index to write next char to in proto buff
static uint8_t proto_buff_ndx;

// TODO
void proto_cmd_motor_get_throttle(char *buff, uint8_t length) {
}

// TODO
void proto_cmd_motor_set_throttle(char *buff, uint8_t length) {
}

void proto_buff_reset(void) {
	proto_buff_ndx = 0;
}

// Get command stuct for current buffer
// Returns 0 for invalid command
struct proto_cmd_info *proto_buff_cmd_info(void) {
	struct proto_cmd_info *cmd;
	uint8_t cmd_ndx = (uint8_t)(proto_buff[0]);

	// Check for valid command
	if(cmd_ndx >= PROTO_CMD_COUNT)
		return 0;
	cmd = &proto_commands[cmd_ndx];
	if(cmd->length <= 1 || cmd->handler == 0)
		return 0;

	return cmd;
}

void proto_init(void) {
	proto_buff_ndx = 0;
}

void proto_got_char(char ch) {
	// Append char to current buffer and increment buff ndx
	proto_buff[proto_buff_ndx] = ch;
	++proto_buff_ndx;

	// Check to see if we got a full command
	struct proto_cmd_info *cmd = proto_buff_cmd_info();
	if(!cmd) {
		// Invalid command, reset buffer
		proto_buff_reset();
		return;
	}
	if(cmd->length == proto_buff_ndx) {
		// We have a full command in buffer
		// Check for command end chars
		if(proto_buff[proto_buff_ndx-2] != '\n'
		   || proto_buff[proto_buff_ndx-1] != '\r') {
			// Invalid command end chars
			proto_buff_reset();
			return;
		}

		// Exec command handler
		cmd->handler(proto_buff, proto_buff_ndx);
		proto_buff_reset();
		return;
	}

	// Check for buffer overrun
	if(proto_buff_ndx >= PROTO_BUFF_SIZE) {
		proto_buff_reset();
		return;
	}
}

