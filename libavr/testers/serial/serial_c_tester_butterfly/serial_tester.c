<<<<<<< .mine
/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2011, and Joe Pardue, All rights reserved.
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
 *  - Neither the name of Joe Pardue nor the names of 
 *    its contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission. 
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
 
 // Some of this code may have elements taken from other code without attribution.
 // If this is the case it was due to oversight while debugging and I apologize.
 // If anyone has any reason to believe that any of this code violates other licenses
 // please contact me with details so that I may correct the situation. // NOTE: THIS IS FOR THE BUTTERFLY
=======
/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2011, and Joe Pardue, All rights reserved.
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
 *  - Neither the name of Joe Pardue nor the names of 
 *    its contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission. 
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
 
 // Some of this code may have elements taken from other code without attribution.
 // If this is the case it was due to oversight while debugging and I apologize.
 // If anyone has any reason to believe that any of this code violates other licenses
 // please contact me with details so that I may correct the situation. 
>>>>>>> .r94

#include "c:\avrtoolbox\libavr\source\elementary\serial\serial.h"
#if defined(BUTTERFLY)
#include "c:\avrtoolbox\libavr\source\board\butterfly\butterfly.h" //"libserial\serial.h"
#endif

<<<<<<< .mine
#include "c:\avrtoolbox\libavr\source\elementary\serial\serial.h"


=======
>>>>>>> .r94
int main(void)
{ 
	uint8_t count = 0;
	uint8_t buf[64];

<<<<<<< .mine
	#if defined(BUTTERFLY)
	butterfly_init();
	#endif
=======
>>>>>>> .r94

	// NOTE: If BUTTERFLY is defined then the serial_being() is bypassed
	// and the usart is set to 19200 regardless of what this says
	serial_begin(57600);

	serial_out("Serial tester 008\n");//,0);

<<<<<<< .mine
=======
	serial_out("Serial tester 013\n");//,0);

>>>>>>> .r94
	// Send a bunch of stuff to see if it poops out
	serial_out("serial_out The quick brown fox jumped over the lazy dog.");
	serial_out("serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("1serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("2serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("3serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("4serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("5serial_out The quick brown fox jumped over the lazy dog.\n");

	char c = 'A';
	uint8_t x = 0x22;
	uint16_t X = 0x1122;

	serial_out("Test character: %c\n", c);

	serial_out("Test hexadecimal integer: %x\n", x);

	serial_out("Test 16-bit hexadecimal integer: %x\n", X);

	uint8_t  my_day = 21;
	uint8_t my_month[] = {"July"};
	uint16_t my_year = 1980;
	
	serial_out("Your date of birth is:\nDay: %d \nMonth: %s \nYear: %d.", my_day, my_month, my_year); 
	
	buf[1] = '\0';
	while(1)
	{
		if(serial_available())
		{
			buf[0] = serial_in();
			serial_write(buf,1);
/*			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				buf[i] = serial_in();
				//usart0_transmit_buffer_insert(serial_read());//usart0_receive_buffer_remove());
			}
			
			serial_write(buf,count);
*/		
			// Test serial_flush
			/*
			serial_write(buf,count);
			serial_flush();
			serial_write(buf,count);
			*/

			// Test usart0_uninit()
			/*
			_delay_ms(500);
			serial_out("Before serial_end()\n",0);
			serial_end();
			serial_out("After serial_end()\n",0);
				serial_begin(57600);
			serial_out("After serial_begin(57600)\n",0);
			*/
		}
	}
}

<<<<<<< .mine
/*void butterfly_init(void)
{
=======
>>>>>>> .r94


<<<<<<< .mine
    ACSR = (1<<ACD);

    /// Disable Digital input on PF0-2 (power save)
    DIDR1 = (7<<ADC0D);

    PORTB = 0xFF;       /// Enable pullups on Ports B and E
    PORTE = 0xFF;
*//*    
    /// boost IntRC to 2Mhz to achieve 19200 baudrate
    CLKPR = (1<<CLKPCE);        /// set Clock Prescaler Change Enable
    /// set prescaler = 4, Inter RC 8Mhz / 4 = 2Mhz
    CLKPR = (1<<CLKPS1);    

    UBRRH = 0;
    UBRRL = 12;

    /// Enable 2x speed
    UCSRA = (1<<U2X);

    /// Enable receiver and transmitter
	// JWP added | 10/22/10
    UCSRB |= (1<<RXEN)|(1<<TXEN)|(0<<RXCIE)|(0<<UDRIE);

    /// Async. mode, 8N1
    UCSRC = (0<<UMSEL)|(0<<UPM0)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
*/
    // JWP commented out 10/22/10  
	// This was killing the usart interrupt and I'm guessing
	// that it should only be in the bootloader code.  
    //MCUCR = (1<<IVCE);       
    //MCUCR = (1<<IVSEL);  ///move interruptvectors to the Boot sector    

// TODO 10/23/10
//    sei(); /// mt __enable_interrupt();
    
    /// mt PCMSK1 = (1<<PORTB6) | (1<<PORTB4);
/*	PCMSK1 = (1<<PINB6) | (1<<PINB4);       // set pin-change interrupt mask
  	EIFR   = (1<<PCIF1);                    // clear external intterupt flag 1
	EIMSK  = (1<<PCIE1);   

}


void OSCCAL_calibration(void)
{
    unsigned char calibrate = 0;//FALSE;
    int temp;
    unsigned char tempL;

    CLKPR = (1<<CLKPCE);        /// set Clock Prescaler Change Enable
    /// set prescaler = 8, Inter RC 8Mhz / 8 = 1Mhz
    CLKPR = (1<<CLKPS1) | (1<<CLKPS0);
    
    TIMSK2 = 0;             ///disable OCIE2A and TOIE2

    ASSR = (1<<AS2);        ///select asynchronous operation of timer2 (32,768kHz)
    
    OCR2A = 200;            /// set timer2 compare value 

    TIMSK0 = 0;             /// delete any interrupt sources
        
    TCCR1B = (1<<CS10);     /// start timer1 with no prescaling
    TCCR2A = (1<<CS20);     /// start timer2 with no prescaling

    while((ASSR & 0x01) | (ASSR & 0x04)); ///wait for TCN2UB and TCR2UB to be cleared

    Delay(1000);    /// wait for external crystal to stabilise
    
    while(!calibrate)
    {
        cli(); /// mt __disable_interrupt();  // disable global interrupt
        
        TIFR1 = 0xFF;   /// delete TIFR1 flags
        TIFR2 = 0xFF;   /// delete TIFR2 flags
        
        TCNT1H = 0;     /// clear timer1 counter
        TCNT1L = 0;
        TCNT2 = 0;      /// clear timer2 counter
           
	while ( !(TIFR2 & (1<<OCF2A)) ); // while ( !(TIFR2 && (1<<OCF2A)) );   // wait for timer2 compareflag
    
        TCCR1B = 0; /// stop timer1

        sei(); /// __enable_interrupt();  // enable global interrupt
    
        if ( (TIFR1 & (1<<TOV1)) ) // if ( (TIFR1 && (1<<TOV1)) )
        {
            temp = 0xFFFF;      /// if timer1 overflows, set the temp to 0xFFFF
        }
        else
        {   /// read out the timer1 counter value
            tempL = TCNT1L;
            temp = TCNT1H;
            temp = (temp << 8);
            temp += tempL;
        }
    
        if (temp > 6250)
        {
            OSCCAL--;   /// the internRC oscillator runs to fast, decrease the OSCCAL
        }
        else if (temp < 6120)
        {
            OSCCAL++;   /// the internRC oscillator runs to slow, increase the OSCCAL
        }
        else
            calibrate = 1;///TRUE;   // the interRC is correct
    
        TCCR1B = (1<<CS10); /// start timer1
    }
}


void Delay(unsigned int millisec)
{
    unsigned char i; // mt int i;
    
    while (millisec--)
        for (i=0; i<125; i++);
}

*/


=======
>>>>>>> .r94
