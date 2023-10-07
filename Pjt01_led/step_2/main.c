#include <stdio.h>
#include <avr/io.h>

extern void led();

int main()
{
	led();	

	while(1);
	return 0;
}
