#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "prime.h"
#include "list.h"
#include "uart.h"
#include "timer.h"
#include "q.h"
#include <avr/interrupt.h>

int main()
{
	int tag;
	struct task task;

	uart_init();
	task_init();
	timer_init();
	adc_init();

	printf("$ ");

	while(1){
		cli();
		tag = task_delete(&task);
		sei();
		if (tag)
			(*(task.fun))(task.arg);
	}
	return(0);
}
