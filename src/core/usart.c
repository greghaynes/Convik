#include "usart.h"
#include "../config.h"
#include "../utils/char_fifo.h"

#include <avr/interrupt.h>

#define UBRR F_CPU/16/USART_BAUDRATE-1

struct usart_ctl {
	struct char_fifo in_fifo;
	struct char_fifo out_fifo;

	char in_buff[USART_BUFF_SIZE];
	char out_buff[USART_BUFF_SIZE];
};

static struct usart_ctl _usart_ctl;

void usart_isr_udre_enable(void) {
	UCSR0B |= (1<<UDRIE0);
}

void usart_isr_udre_disable(void) {
	UCSR0B &= ~(1<<UDRIE0);
}

/* USART Receive byte interrupt handler */
ISR(USART_RX_vect) {
}

/* USART Data register empty handler */
ISR(USART_UDRE_vect) {
	// Check that data register is empty
	// If not, return
	if(!UCSR0A && (1<<UDRE0)) return;

	// Pop byte to send
	char ch;
	if(char_fifo_pop(&_usart_ctl.out_fifo, &ch)) {
		// Fifo is empty, shouldnt happen
		usart_isr_udre_disable();	
		return;
	}

	// Disable UDRE interrupt if no more data to send
	if(char_fifo_is_empty(&_usart_ctl.out_fifo))
		usart_isr_udre_disable();

	// Send byte
	UDR0 = ch;
}

void usart_init() {
	int ubrr = UBRR;

	// Initialize FIFOs
	char_fifo_init(&_usart_ctl.in_fifo, _usart_ctl.in_buff, USART_BUFF_SIZE);
	char_fifo_init(&_usart_ctl.out_fifo, _usart_ctl.out_buff, USART_BUFF_SIZE);

	// Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	// Enable receive interrupt and transmit and receive
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);

	// Set frame 8 n 2
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

uint8_t usart_send_char(unsigned char ch) {
	// Push char into out buffer
	if(char_fifo_push(&_usart_ctl.out_fifo, ch))
		return 1;

	// Enable data register empty interrupt
	usart_isr_udre_enable();

	return 0;
}

