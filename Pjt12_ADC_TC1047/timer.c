#include <stdlib.h>
#include "timer.h"
#include "prime.h"
#include <stdio.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include <string.h>
#include "q.h"
#include "uart.h"
#include "adc.h"

#define EOT 0x04
#define ESC 0x1B


struct timer *get_timer()
{
	struct timer *tp;

	tp = (struct timer *)malloc(sizeof(*tp));
	return(tp);
}
struct timer *Thread = NULL;

void insert_timer(struct task *tskp, int ms)
{
	int	total;
	struct timer *tp, *cp, *pp;

	tp = get_timer();
	tp->task = *tskp;
	tp->time = ms;

	if (Thread == NULL){
		Thread = tp, tp->link = NULL;
		return;
	}

	pp = NULL, total=0;
	for (cp = Thread; cp; cp = cp->link) {
		total += cp->time;
		if(total >= ms)
			break;
		pp = cp;
	}

	if (pp == NULL){
		cp->time -= tp->time;
		tp->link = cp, Thread = tp;
	}
	else if (cp == NULL) {
		tp->time -= total;
		pp->link = tp;
		tp->link = NULL;
	}
	else{
		total -= cp->time;
		tp->time -= total;
		cp->time -= tp->time;
		pp->link = tp;
		tp->link = cp;
	}
}

void tour_timer()
{
	struct timer *cp;
	int total = 0;

	printf("\n");
	for(cp = Thread; cp != NULL; cp = cp->link){
		total += cp->time;
		printf("-->%d(%d) ", cp->time, total);
	}
	printf("\n");
}
void free_timer()
{
	struct timer *cp;

	for( ; Thread != NULL;) {
		cp = Thread;
		Thread = cp->link;
		free(cp);
		}
}
void app_timer(char *ap)
{
	char 	buf[8];
	int		ms;
	struct task tsk;

	while(1) {
		printf(">> ");
		if(fgets(buf, 8, stdin) == NULL || (ms = atoi(buf)) == 0)
			break;

		insert_timer(&tsk, ms);
	}
	tour_timer();
	free_timer();
}

void timer_init(){
	TCNT2 = 0;
	sbi(ASSR, AS2);
	sbi(TIMSK2, TOIE2);
	sbi(TCCR2B, CS20); sbi(TCCR2B, CS21);
}

ISR(TIMER2_OVF_vect)
{
	if(!Thread)
		return;
	if(--Thread->time == 0)
			timer_expire();
}

void timer_expire(void)
{
	struct timer *tp;

	for(; Thread != NULL && !Thread->time; ) {
		tp = Thread, Thread = tp->link;

		task_insert(&tp->task);

		free(tp);
		}
}

//task 
void task_init()
{
	Task_f = Task_r = 0;
}

int task_insert(struct task *tskp)
{
	if((Task_r + 1) % MAX_TASK == Task_f)
		return(0);
	Task_r = (Task_r + 1) % MAX_TASK;
	Task_q[Task_r] = *tskp;
	return(1);
}

int task_delete(struct task *tskp)
{
	if(Task_r == Task_f)
		return(0);
	Task_f = (Task_f + 1) % MAX_TASK;
	*tskp = Task_q[Task_f];
	return(1);
}

void task_cmd(char *arg)
{
	char buf[64], *cp0, *cp1, *cp2, *cp3;
	struct task task;
	int ms;

	if(!uart_peek()) return;

	if(gets(buf) == NULL) {
		printf("logout, good bye !!!\n");
		while(1);
	}

	cp0 = strtok(buf, " \t\n\r" );
	cp1 = strtok(NULL, " \t\n\r" );
	cp2 = strtok(NULL, " \t\n\r" );
	cp3 = strtok(NULL, " \t\n\r" );

	if(cp0 == NULL) {
	printf( "$ "); return;
	}

	if(!strcmp(cp0, "prime"))
		task_prime(cp1);
	else if(!strcmp(cp0, "tc1047"))
		task_tc1047("");
	else if(!strcmp(cp0, "timer")) {
		if (cp1 == NULL) {
			printf( "!!!-222\n");
			printf("$ ");
			return;
		}
		ms = atoi(cp1) / 256;
		if(!strcmp(cp2, "prime")) {
			task.fun = task_prime;
			if(cp3) strcpy(task.arg, cp3);
			else	strcpy(task.arg, "");
			cli();
			insert_timer(&task, ms);
			sei();
		}
		else printf("!!!-333\n");
	}
	else printf("Unknown command...\n");

	printf("$ ");
}


static int echo_mode = 1;

ISR(USART0_RX_vect)
{
	struct task task;
	char ch;

	ch = UDR0;
	if(ch == ESC){
		echo_mode = (echo_mode+1) & 0x01;
		return;
	}
	if(ch != EOT) {
		if( ch == '\r') ch = '\n';
		if(echo_mode) uart_echo(ch);
	}
	qi_insert(ch);
	if(ch == EOT || ch == '\n' ) {
		task.fun = task_cmd;
		strcpy(task.arg, "");
		task_insert(&task);
	}
}

int qi_peek()
{
	if(fi == ri)
		return 0;
	else
		return(qi[(fi + 1) % QI_SIZE]);
}
int uart_peek()
{
	return(qi_peek());
}
