#include <stdio.h>
#include "uart.h"

int main()
{
	char c;
	uart_init();
	while(1) {
		for (c = 'A'; c <= 'Z'; c++)
			uart_putchar(c);
		uart_putchar( '\n' );

		uart_putstr( "ABCD\n" );
	}
	return 0;
}
