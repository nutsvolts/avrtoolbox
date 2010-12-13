/*****************************************************
	devices.c Joe Pardue Decembrer 11, 2010

	AT THE PRESENT TIME,THIS IS ONLY NEED FOR THE BUTTERFLY
******************************************************/

/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2010, Smiley Micros, All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 *   
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *   
 *  - Neither the name of the Smiley Micros nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission. 
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/*****************************************************
	This program holds the special functions, if any
	required by specific devices such as the Butterfly
******************************************************/
#include "device.h"

// Only compile if Butterfly is defined
#if defined(Butterfly)

// Stuff extracted from Atmel Butterfly Application

void butterfly_init()
{
// NOTE this all copied directly from the original Butterfly source code
// so it uses a different method for naming registers than the rest of the code
// updated register names to fit new io headers - why do they keep changing this?

    OSCCAL_calibration();   // Calibrate the OSCCAL byte

    ACSR = (1<<ACD);

    // Disable Digital input on PF0-2 (power save)
    DIDR1 = (7<<ADC0D);

    PORTB = 0xFF;       // Enable pullups on Ports B and E
    PORTE = 0xFF;
    
    // boost IntRC to 2Mhz to achieve 19200 baudrate
    CLKPR = (1<<CLKPCE);        // set Clock Prescaler Change Enable
    // set prescaler = 4, Inter RC 8Mhz / 4 = 2Mhz
    CLKPR = (1<<CLKPS1);    

    UBRRH = 0;//(unsigned char)(baudrate>>8);
    UBRRL = 12;//(unsigned char)baudrate;

    // Enable 2x speed
    UCSRA = (1<<U2X);

    // Enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN)|(0<<RXCIE)|(0<<UDRIE);

    // Async. mode, 8N1
    UCSRC = (0<<UMSEL)|(0<<UPM1)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
        
    MCUCR = (1<<IVCE);       
    MCUCR = (1<<IVSEL);             //move interruptvectors to the Boot sector    

    sei(); // mt __enable_interrupt();
    
    // mt PCMSK1 = (1<<PORTB6) | (1<<PORTB4);
	PCMSK1 = (1<<PINB6) | (1<<PINB4);       // set pin-change interrupt mask
  	EIFR   = (1<<PCIF1);                    // clear external intterupt flag 1
	EIMSK  = (1<<PCIE1);  
}



/*****************************************************
	Oscillator Calibration
	The following code is taken directly from Martin Thoma's
	port of Atmel's IAR Butterfly software to GCC
******************************************************/
/*****************************************************************************
*
*   Function name : OSCCAL_calibration
*
*   Returns :       None
*
*   Parameters :    None
*
*   Purpose :       Calibrate the internal OSCCAL byte, using the external 
*                   32,768 kHz crystal as reference
*
*****************************************************************************/
void OSCCAL_calibration(void)
{
    unsigned char calibrate = 0;//FALSE;
    int temp;
    unsigned char tempL;

    CLKPR = (1<<CLKPCE);        // set Clock Prescaler Change Enable
    // set prescaler = 8, Inter RC 8Mhz / 8 = 1Mhz
    CLKPR = (1<<CLKPS1) | (1<<CLKPS0);
    
    TIMSK2 = 0;             //disable OCIE2A and TOIE2

    ASSR = (1<<AS2);        //select asynchronous operation of timer2 (32,768kHz)
    
    OCR2A = 200;            // set timer2 compare value 

    TIMSK0 = 0;             // delete any interrupt sources
        
    TCCR1B = (1<<CS10);     // start timer1 with no prescaling
    TCCR2A = (1<<CS20);     // start timer2 with no prescaling

    while((ASSR & 0x01) | (ASSR & 0x04));       //wait for TCN2UB and TCR2UB to be cleared

    Delay(1000);    // wait for external crystal to stabilise
    
    while(!calibrate)
    {
        cli(); // mt __disable_interrupt();  // disable global interrupt
        
        TIFR1 = 0xFF;   // delete TIFR1 flags
        TIFR2 = 0xFF;   // delete TIFR2 flags
        
        TCNT1H = 0;     // clear timer1 counter
        TCNT1L = 0;
        TCNT2 = 0;      // clear timer2 counter
           
	while ( !(TIFR2 & (1<<OCF2A)) ); // while ( !(TIFR2 && (1<<OCF2A)) );   // wait for timer2 compareflag
    
        TCCR1B = 0; // stop timer1

        sei(); // __enable_interrupt();  // enable global interrupt
    
        if ( (TIFR1 & (1<<TOV1)) ) // if ( (TIFR1 && (1<<TOV1)) )
        {
            temp = 0xFFFF;      // if timer1 overflows, set the temp to 0xFFFF
        }
        else
        {   // read out the timer1 counter value
            tempL = TCNT1L;
            temp = TCNT1H;
            temp = (temp << 8);
            temp += tempL;
        }
    
        if (temp > 6250)
        {
            OSCCAL--;   // the internRC oscillator runs to fast, decrease the OSCCAL
        }
        else if (temp < 6120)
        {
            OSCCAL++;   // the internRC oscillator runs to slow, increase the OSCCAL
        }
        else
            calibrate = 1;//TRUE;   // the interRC is correct
    
        TCCR1B = (1<<CS10); // start timer1
    }
}


/*****************************************************************************
*
*   Function name : Delay
*
*   Returns :       None
*
*   Parameters :    unsigned int millisec
*
*   Purpose :       Delay-loop
*
*****************************************************************************/
void Delay(unsigned int millisec)
{
    unsigned char i; // mt int i;
    
    while (millisec--)
        for (i=0; i<125; i++);
}

#endif
