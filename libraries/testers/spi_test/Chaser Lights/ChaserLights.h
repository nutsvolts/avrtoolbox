// Constants used to calculate the register
// settings for each device baudrate
#if defined(Butterfly)
#include <avr/interrupt.h>
#define F_CPU 1000000L
#elif (defined(Arduino) || defined(BeAVR40))
#define F_CPU 16000000L
#endif 

#include <util\delay.h>
