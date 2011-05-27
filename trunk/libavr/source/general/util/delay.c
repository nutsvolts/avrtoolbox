#include <util\delay.h>

void delay(uint16_t ms);

void delay(uint16_t ms)
{
	for(int i = 0 ; i < ms ; i++)
	{
		_delay_ms(1);
	}
}
