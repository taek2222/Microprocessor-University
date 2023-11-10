#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "linked.h"
#include "time.h"
#include "uart.h"
#include "io.h"
#define E0T 0x04

int is_prime(int n);
void app_prime(char *ap);

int main()
{
	char cmd[128], *cp, *ap, *ab;

	uart_init();
	sei();
	while(1) {
		printf("$ ");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		if((cp = strtok(cmd, "\n\r\t    ")) == NULL) continue;
		ap = strtok(NULL, "\n\r\t  ");
		ab = strtok(NULL, "\n\r\t  ");

		if(!strcmp(cmd, "prime")) app_prime(ap);
		else if (!strcmp(cp, "list" )) app_list(ap);
		else if (!strcmp(cp, "timer" )) app_timer(ap);
		else if (!strcmp(cp, "add" )) app_add(ap, ab);
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

void app_prime(char *ap)
{
	int t = 2000, count = 0, n;

	if (ap) t = atoi(ap);
	for(n = 2; n <= t; n++) {
		if(is_prime(n)) {
			count++;
			printf( "%d is a prime. " "number !!!\n", n);
		}
	}
	printf("count = %d \n", count);
}

void app_add(char *ap, char *ap1)
{
	int num1, num2;
	num1 = atoi(ap);
	num2 = atoi(ap1);

	printf(" %d \n", num1 + num2);
}
