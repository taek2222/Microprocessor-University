#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

int main() {
	int i;
	uart_init();
	sei();

	for(i = 0; i < 10; i++) {
		uart_putstart( "I love you. \n" );
		uart_putstart( "You love me. \n" );
		uart_putstart( "He loves her. \n" );
	}

	uart_putstart( "End !!! \n");
	while(1);
	return 0;
}

ISR(USART0_TX_vect)
{
	char ch = buf[bufi];
	if(!ch) {
		txend = 1; return;
	}
	if (ch == '\n') buf[bufi] = '\r';
	else			bufi++;
	UDR0 = ch;
}
