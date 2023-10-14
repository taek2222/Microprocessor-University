#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include "uart.h"

void uart_init()
{
	UBRR0H = 0x00; UBRR0L = 0x07;
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << TXCIE0);
}

char buf[64];
int volatile bufi, txend = 1;

void uart_putstart(char str[])
{
	char ch;
	while(!txend); txend = 0;
	
	strcpy(buf, str); bufi = 0;
	ch = buf[bufi++];

	UDR0 = ch;
}
