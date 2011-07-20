#ifndef CONVIK_CHAR_BUFFER_H
#define CONVIK_CHAR_BUFFER_H

#include <avr/io.h>

struct char_buffer {
	char *data;
	uint8_t size;
	uint8_t end_ndx;
};

void char_buffer_init(struct char_buffer *buff, char *data_buff, uint8_t size);

/* Returns 1 if not enough space available. Returns 0 otherwise. */
uint8_t char_buffer_append(struct char_buffer *buff, char *data, uint8_t length);

#endif

