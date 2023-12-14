#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_prime(int n) {
	int i;
	for (i=2; i<=n/2; i++)
		if((n % i) == 0) return 0;
	return(1);
}

void app_prime(char *ap){
	int n, count = 0,t=2000;
	if(ap) t = atoi(ap);
	for (n = 2; n <= t; n++){
		if (is_prime(n)){
			count ++;
			printf( "%d is a prime number !!!\n" , n);
		}
	}
	printf( "count=%d\n", count);
}

void app_add(char *ap, char *bp){

    int a, b, s;
	a=atoi(ap);
	b=atoi(bp);

	s = a+b;
	printf("%d", s);
	printf("\n");

 }

void cal(char *ap){
	int a,b;
	char c;
	sscanf(ap, "%d%c%d", &a,&c,&b); 
	
	switch(c){
		case '+':
			printf("%d \n", a+b);
			break;
		case '-':
			printf("%d \n", a-b);
			break;
		case '*':
			printf("%d \n", a*b);
			break;
		case '/':
			printf("%d \n", a/b);
			break;
	}
}

void task_prime(char *ap)
{
	int n, t = 2000, count=0;

	if(ap && *ap) t = atoi(ap);
	for (n = 2; n<= t; n++) {
		if (is_prime(n)){
			count++;
			printf("%d is a prime number !!!\n",  n);
		}
	}
	printf("count=%d\n", count);
}
