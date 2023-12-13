#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "io.h"
#define E0T 0x04

int uart_putchar(char ch, FILE  *stream);
int uart_getchar(FILE *stream);

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE Mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

char uart_busy;

void uart_init()
{
	stdin = &Mystdin; stdout = &Mystdout;
	q_init();
	uart_busy = 0;

	UBRR0H = 0x00; UBRR0L = 0x07;
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, RXCIE0);
}

int uart_putchar(char ch, FILE *stream)
{
	if (ch == '\n') uart_putchar('\r', stream);

	cli();
	if(!uart_busy) {
		UDR0 = ch;
		uart_busy = 1;
	}
	else {
		while(qo_insert(ch) == 0) {
			sei();
			_delay_us(100);
			cli();
		}
	}
	sei();
	return 1;
}

int uart_getchar(FILE *stream)
{
	char ch;

	do {
		cli();
		ch = qi_delete();
		sei();
	} while (ch == 0);

	if (ch == E0T) return -1;
	else			return (ch);
}

void uart_echo(char ch) // 수신 인터럽트 사용자 출력 부분
{
	if (ch == '\n') uart_echo( '\r' );
	if (!uart_busy) { // 0 False, 1 True
		UDR0 = ch;
		uart_busy = 1; // UART : 0 (바쁘지 않다), UART : 1 (바쁘다)
	}
	else
		qo_insert(ch);
}
