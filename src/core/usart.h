/**
 * Copyright Gregory Haynes <greg@greghaynes.net> 2011
 * All source code is released under the terms of the MIT License.
 * See LICENSE for more information.
 */

#ifndef CONVIK_USART_H
#define CONVIK_USART_H

#include <avr/io.h>

/* Initialize serial.
 * Must call before use.  */
void usart_init();

struct char_fifo *usart_recv_fifo(void);

/* Asynchronously sends char over serial.
 * Returns 1 for full buffer, 0 otherwise.  */
uint8_t usart_send_char(unsigned char ch);

#endif

