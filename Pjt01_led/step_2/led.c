#include <avr/io.h>

void led()
{
	DDRL = 0xff;
	PORTL = 0x00;
}
