#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "queue.h"

int main()
{
	uart_init();
	sei();

	app_prime(2000);

	while(1);

	return 0;
}

ISR(USART0_TX_vect)
{
	char ch;

	if ((ch = q_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}
