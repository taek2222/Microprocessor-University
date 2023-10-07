#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main()
{
	led_init();

	while(1) {
		for(uint8_t i = 0; i < 8; i++)
		{
			led_on(i);
			_delay_ms(150);
			led_off(i);
			}
	}
	return 0;
}
