#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main()
{
	led_init();

	while(1) {
		led_on_all();
		_delay_ms(1500);
		led_off_all();
		_delay_ms(1500);
	}
	return 0;
}
