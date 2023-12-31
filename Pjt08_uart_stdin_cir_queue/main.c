#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "io.h"
#define E0T 0x04

void app_prime(int t);
int is_prime(int n);

int main()
{
	char cmd[128], *cp;
	int n = 0;

	uart_init();
	sei();
	while(1) {
		printf("$ ");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		if((cp = strtok(cmd, "\n\r\t    ")) == NULL) continue;
		if(!strcmp(cmd, "prime")) app_prime(2000);
		else						printf("Unknown command ...\n");
	}
	printf( "logout, good bye !!!\n");
	while(1); return 0; 
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
	if ( ch != E0T) {
		if(ch == '\r') ch = '\n';
		uart_echo(ch);
	}
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

