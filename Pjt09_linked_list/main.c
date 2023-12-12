#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h> // AVR ���ͷ�Ʈ
#include "linked.h" // Linked List
#include "uart.h" // UART
#include "io.h" // IO
#include "prime.h" // �Ҽ� ã��
#define E0T 0x04

int is_prime(int n);
void app_prime(char *ap);

int main()
{
	char cmd[128], *cp, *ap;

	uart_init(); // UART ����� ���� �� �ʱ�ȭ
	sei(); // ���ͷ�Ʈ Ȱ��ȭ
	while(1) {
		printf("$ ");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL) // Enter�� �Է� ���
			break;
		if((cp = strtok(cmd, "\n\r\t    ")) == NULL) continue;
		ap = strtok(NULL, "\n\r\t  ");

		if(!strcmp(cp, "prime")) app_prime(ap);
		else if (!strcmp(cp, "list" )) app_list(ap);
		else						printf("Unknown command ...\n");
	}
	printf( "logout, good bye !!!\n");
	while(1); return 0;
}

ISR(USART0_TX_vect) // ���� ���ͷ�Ʈ 
{
	char	ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}

ISR(USART0_RX_vect) // ���� ���ͷ�Ʈ
{
	char ch;

	ch = UDR0;
	if (ch != E0T) {
		if(ch == '\r') ch = '\n'; // \r, \n Enter �ǹ�
		uart_echo(ch);
	}
	qi_insert(ch);
}
