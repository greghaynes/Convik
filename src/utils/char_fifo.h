/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#ifndef CHAR_FIFO_H
#define CHAR_FIFO_H

#include <avr/io.h>

struct char_fifo {
	char *buff;
	uint8_t buff_size;
	uint8_t pop_ndx;
	uint8_t push_ndx;
};

/* Initialize a char fifo */
void char_fifo_init(struct char_fifo *cf, char *buff, uint8_t buff_size);

/* Return 0 if fifo is empty, otherwise return 1. */
uint8_t char_fifo_is_empty(struct char_fifo *cf);

/* Return 0 if fifo is full, otherwise return 1. */
uint8_t char_fifo_is_full(struct char_fifo *cf);

/* Push char into fifo.
 * Returns 0 on success, 1 on falure (full fifo). */
uint8_t char_fifo_push(struct char_fifo *cf, char ch);

/* Pop char into *ch.
 * Returns 0 on success, 1 on failure (empty fifo). */
uint8_t char_fifo_pop(struct char_fifo *cf, char *ch);

#endif

