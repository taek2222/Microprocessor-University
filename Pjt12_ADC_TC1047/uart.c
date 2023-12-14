#include <avr/io.h>
#include <stdio.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "q.h"
#include "adc.h"
#include <util/delay.h>
#define EOT 0x04

int uart_putchar(char ch, FILE *stream), uart_getchar(FILE *stream);

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE Mystdin  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
char uart_busy;

void uart_init()
{
	stdin = &Mystdin;
	stdout = &Mystdout;
	uart_busy = 0;
	q_init();
	UBRR0H = 0x00; UBRR0L = 0x07;
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, RXCIE0);
}

int uart_getchar(FILE *stream)
{
	char ch;

	do{
		cli();
		ch = qi_delete();
		sei();
		}while (ch == 0);

		if (ch == EOT) return(-1);
		else		   return(ch);
}

int uart_putchar(char ch, FILE *stream)
{
	if(ch == '\n') uart_putchar( '\r' , stream);

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

	return(1);
}



void uart_echo(char ch)
{
	if (ch == '\n') uart_echo( '\r' );
	if (!uart_busy) {
			UDR0 = ch;
			uart_busy = 1;
	}
	else
		qo_insert(ch);
}

ISR(USART0_TX_vect)
{
	char ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}

ISR(ADC_vect)
{
	uint16_t	data;
	char		arg[8];

	data = ADCW & 0x03ff;
	cbi(ADCSRA, ADEN);

	sprintf(arg, "%d", data);
	task_tc1047(arg);
}
