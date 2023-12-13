#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h> // AVR 인터럽트
#include "linked.h" // Linked List
#include "uart.h" // UART
#include "io.h" // IO
#include "prime.h" // 소수 찾기
#define E0T 0x04

int main()
{
	char cmd[128], *cp, *ap; // cmd 배열 : 입력 내용 저장, cp 포인터 : 명령어, ap 포인터 : 인자

	uart_init(); // UART 통신을 설정 및 초기화
	sei(); // 인터럽트 활성화
	while(1) {
		printf("$ ");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL) // Enter의 입력 대기
			break;
		if((cp = strtok(cmd, "\n\r\t    ")) == NULL) continue; // \n\r\t 기준 토큰 분리 (명령어)
		ap = strtok(NULL, "\n\r\t  "); // \n\r\t 기준 토큰 분리 (인자)

		if(!strcmp(cp, "prime")) app_prime(ap); // prime 명령어 ap 인자 전달
		else if (!strcmp(cp, "list" )) app_list(ap); // list 명령어 ap 인자 전달
		else						printf("Unknown command ...\n");
	}
	printf( "logout, good bye !!!\n");
	while(1); return 0;
}

ISR(USART0_TX_vect) // 송신 인터럽트 
{
	char	ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}

ISR(USART0_RX_vect) // 수신 인터럽트
{
	char ch;

	ch = UDR0;
	if (ch != E0T) {
		if(ch == '\r') ch = '\n'; // \r, \n Enter 의미
		uart_echo(ch);
	}
	qi_insert(ch);
}
