#include <stdio.h>
#include <avr/io.h>

int main()
{
	DDRL = 0xff;
	PORTL = 0x00;

	while(1);
	return 0;
}
