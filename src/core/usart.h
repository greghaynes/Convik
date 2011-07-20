#ifndef CONVIK_USART_H
#define CONVIK_USART_H

#include <avr/io.h>

/* Initialize serial.
 * Must call before use.  */
void usart_init();

/* Asynchronously sends char over serial.
 * Returns 1 for full buffer, 0 otherwise.  */
uint8_t usart_send_char(unsigned char ch);

#endif

