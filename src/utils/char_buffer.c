#include "char_buffer.h"

void char_buffer_init(struct char_buffer *buff, char *data_buff, uint8_t size) {
	buff->data = data_buff;
	buff->size = size;
	buff->end_ndx = 0;
}

uint8_t char_buffer_append(struct char_buffer *buff, char *data, uint8_t length) {
	uint8_t i;

	// Check for available space
	if(buff->size < (buff->end_ndx + length))
		return 1;

	// Append data
	for(i = 0;i < length;i++)
		buff->data[i] = data[i];

	// Update end_ndx
	buff->end_ndx += length;

	return 0;
}

void char_buffer_reset(struct char_buffer *buff) {
	buff->end_ndx = 0;
}

uint8_t char_buffer_length(struct char_buffer *buff) {
	return buff->end_ndx;
}

