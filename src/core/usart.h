#ifndef CONVIK_USART_H
#define CONVIK_USART_H

#include <avr/io.h>

void usart_init();

void usart_send_char(unsigned char ch);

#endif

