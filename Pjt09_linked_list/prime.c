<<<<<<< HEAD
#include <stdio.h>

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
=======
#include <stdio.h>

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
>>>>>>> e37c7443ce406de039cbbb9e94f9a53a8f370edf
