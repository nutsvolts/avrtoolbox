// NOTE: THIS IS FOR THE BUTTERFLY

//#define BUTTERFLY

void butterfly_init(void);
void OSCCAL_calibration(void);
void Delay(unsigned int millisec);


#include "c:\avrtoolbox\libavr\source\elementary\serial\serial.h" //"libserial\serial.h"

int main(void)
{
	uint8_t count = 0;
	uint8_t buf[64];

	//#if defined(BUTTERFLY)
	butterfly_init();
	//#endif

	// NOTE: If BUTTERFLY is defined then the serial_being() is bypassed
	// and the usart is set to 19200 regardless of what this says
	serial_begin(19200);


/*
	buf[0] = 'H';
	buf[1] = 'o';
	buf[2] = 'w';
	buf[3] = 'd';
	buf[4] = 'y';
	buf[5] = 0;

	serial_write(buf,6);
	// Insert a delay to keep this from stepping on the next statement
	delay(10);
*/
	serial_out("Hello Butterfly 002\n");//,0);

	// Send a bunch of stuff to see if it poops out
	serial_out("serial_out The quick brown fox jumped over the lazy dog.");

	serial_out("serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("1serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("2serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("3serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("4serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("5serial_out The quick brown fox jumped over the lazy dog.\n");

/**/
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
	
	while(1)
	{
		delay(1000);
		usart0_transmit_buffer_insert('#');	

		if(serial_available())
		{
			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				buf[i] = serial_in();
				//usart0_transmit_buffer_insert(serial_read());//usart0_receive_buffer_remove());
			}
			
			serial_write(buf,count);
		
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

void butterfly_init(void)
{

    OSCCAL_calibration();   /// Calibrate the OSCCAL byte

    ACSR = (1<<ACD);

    /// Disable Digital input on PF0-2 (power save)
    DIDR1 = (7<<ADC0D);

    PORTB = 0xFF;       /// Enable pullups on Ports B and E
    PORTE = 0xFF;
/*    
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
	PCMSK1 = (1<<PINB6) | (1<<PINB4);       // set pin-change interrupt mask
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




