#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "io.h"
#include <stdlib.h>

void app_prime(int t);
int is_prime(int n);

int main()
{
	char cmd[128], ch;
	int n = 0;

	uart_init();
	sei();
	printf("$ ");
	while(1) {
		cli();
		ch = qi_delete();
		sei();
		if(ch) {
			if(ch == '\r') continue;
			if(ch == '\n') {
				cmd[n] = 0;
				if(!strcmp(cmd, "app")) app_prime(2000);
				else printf(" Unkonwn command... \n");
				n = 0;
				printf("$ ");
			}
			else
				cmd[n++] = ch;
		}
	}
	return 0;
}

ISR(USART0_TX_vect)
{
	char	ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}

ISR(USART0_RX_vect)
{
	char ch;

	ch = UDR0;
	qi_insert(ch);
}

int is_prime(int n) {
	int i;
	for( i = 2; i <= n/2; i++)
		if((n%i) == 0)
			return 0;
	return 1;
}

void app_prime(int t)
{
	int n, count = 0;
	for(n = 2; n <= t; n++) {
		if(is_prime(n)) {
			count++;
			printf( "%d is a prime. " "number !!!\n", n);
		}
	}
	printf("count = %d \n", count);
}

