#include "../config.h"
#include "usart.h"

#define UBRR F_CPU/16/BAUDRATE-1

void usart_init() {
	int ubrr = UBRR;

	// Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	// Enable transmit and receive
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// Set frame 8 n 2
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void usart_send_char(unsigned char ch) {
	// Wait until transmit buffer is empty
	while ( !( UCSR0A & (1<<UDRE0)) );

	// Write char to transmit buffer
	UDR0 = ch;
}

