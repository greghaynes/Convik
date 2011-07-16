#include "proto.h"
#include "motor.h"

#define PROTO_BUFF_SIZE 9

void proto_cmd_motor_set_throttle(char *buff, uint8_t length);
void proto_cmd_motor_get_throttle(char *buff, uint8_t length);

struct proto_cmd_info {
	uint8_t length;
	void (*handler)(char *buff, uint8_t length);
};

// Commands
static struct proto_cmd_info proto_commands[3] = {
	{ 0, 0 }, // Invalid
	{ 4, proto_cmd_motor_set_throttle }, // Set throttle
	{ 3, proto_cmd_motor_get_throttle }, // Get throttle
};

static char proto_buffs[2][PROTO_BUFF_SIZE];

// The proto buff to write into
static uint8_t proto_buff_current;

// index to write next char to in proto buff
static uint8_t proto_buff_ndx;

// TODO
void proto_cmd_motor_get_throttle(char *buff, uint8_t length) {
}

// TODO
void proto_cmd_motor_set_throttle(char *buff, uint8_t length) {
}

// TODO
void proto_got_char(char ch) {
}

