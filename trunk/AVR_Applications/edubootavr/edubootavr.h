/*****************************************************
	edubootavr.h 7/22/10 Joe Pardue
******************************************************/

#include <avr/io.h>
#include <avr/pgmspace.h> 
#include <avr/boot.h>
#include <avr/wdt.h>


/*****************************************************
	Remove '//' from device you are using
	Add '//' to devices you are not using
******************************************************/
#define ATmega644
//#define ATmega32
//#define Butterfly
//#define Arduino

#if defined(Butterfly)
#include <avr/interrupt.h>
#endif


//#define	BOOT_STATE_PORT			PORTD
//#define	BOOT_STATE_PIN			PIND
//#define	BOOT_STATE_PIN_NUMBER	PIND7


#if defined(ATmega644)

	// This isn't correct, but apparently irrelevant
	#define SUPPORTED_DEVICE_CODE 	0x73

	// Signature bytes for ATmega168
	#define	SIGNATURE_BYTE_1		0x1E
	#define	SIGNATURE_BYTE_2		0x96
	#define	SIGNATURE_BYTE_3		0x09

#elif defined(ATmega328) || defined(Arduino)

	// TODO: INCORRECT - BUT CAN THIS BE ELIMINATED?
	#define SUPPORTED_DEVICE_CODE 	0x73

	// Signature bytes for ATmega328
	#define	SIGNATURE_BYTE_1		0x1E
	#define	SIGNATURE_BYTE_2		0x95
	#define	SIGNATURE_BYTE_3		0x0F

#elif defined(ATmega32)

	// This isn't correct, but apparently irrelevant
	#define SUPPORTED_DEVICE_CODE 	0x73

	// Signature bytes for ATmega168
	#define	SIGNATURE_BYTE_1		0x1E
	#define	SIGNATURE_BYTE_2		0x95
	#define	SIGNATURE_BYTE_3		0x02

#elif defined(ATmega168)

	#define SUPPORTED_DEVICE_CODE 	0x73

	// Signature bytes for ATmega168
	#define	SIGNATURE_BYTE_1		0x1E
	#define	SIGNATURE_BYTE_2		0x94
	#define	SIGNATURE_BYTE_3		0x06

#elif (defined(ATmega169) || defined(Butterfly))

	#define SUPPORTED_DEVICE_CODE 	0x79

	// Signature bytes for ATmega169
	#define	SIGNATURE_BYTE_1		0x1E
	#define	SIGNATURE_BYTE_2		0x94
	#define	SIGNATURE_BYTE_3		0x05

#else
	#error "unsupported"
#endif
/*
#if defined(ATmega644) || defined (ATmega328)
#define BAUD 57600
#elif defined(Butterfly)
#define BAUD 19200
#else
	#error "BAUD undefined"
#endif
*/
// Used by chipErase function
#define BOOTSIZE 512

#define USART_RX_BUFFER_SIZE SPM_PAGESIZE

// AVR109 Command Parser declaration
static void AVR109CommandParser(void);

// AVR109 Command declarations
//static void enterProgramMode(void);
static void autoIncrementAddress(void);
static void setAddress(void);
static void chipErase(void);
static void selectDeviceType(void);
static void readSignatureBytes(void);
static void returnSupportedDeviceCodes(void);
static void returnSoftwareIdentifier(void);
static void returnProgrammerType(void);
static void checkBlockSupport(void);
static void blockFlashLoad(uint16_t size);
static void blockFlashRead(uint16_t size);
static void startBlockAction(uint8_t);
static void exitBootloader(void);

// Function pointer to jump to the applicaion memory section
static void (*application_ptr)( void ) = 0x0000; 

// 12/19/10 JWP test 
#define LED
#if defined (LED)
void flash_led(uint8_t);
#endif

/*****************************************************
	Global variable Declarations
******************************************************/

// SRAM Page buffer for flash page pre-load
uint8_t pageBuffer[SPM_PAGESIZE];

// AVR109 uses a global address
uint16_t address;

/*****************************************************
	From Mike Perks, a generous AVRFreak - modified quite a bit
******************************************************/
/* defines for the various USART registers */
#if defined(ATmega32) || defined(Butterfly)
	
	#define BAUD 57600
	#define F_CPU 16000000L

   // ATMega with one USART 
   #define USART_BAUD_RATE_LOW        	UBRRL
   #define USART_CONTROL_STATUS_REG_A	UCSRA
   #define USART_CONTROL_STATUS_REG_B	UCSRB
   #define USART_CONTROL_STATUS_REG_C	UCSRC
   #define USART_ENABLE_TRANSMITTER		TXEN
   #define USART_ENABLE_RECEIVER		RXEN
   #define USART_READY_TO_TRANSMIT		UDRE
   #define USART_TRANSMIT_COMPLETE		TXC
   #define USART_RECEIVE_COMPLETE		RXC
   #define USART_DATA_REG				UDR
   #define USART_STOP_BIT_SELECT 		USBS
   #define USART_CHARACTER_SIZE_0 		UCSZ0
   #define USART_CHARACTER_SIZE_1 		UCSZ1
   #define USART_REGISTER_SELECT		URSEL

#elif defined(ATmega644)

	#define BAUD 57600
	#define F_CPU 16000000L

   // ATMega with two USARTs - USART 0
   #define USART_BAUD_RATE_LOW			UBRR0L
   #define USART_CONTROL_STATUS_REG_A	UCSR0A
   #define USART_CONTROL_STATUS_REG_B	UCSR0B
   #define USART_CONTROL_STATUS_REG_C	UCSR0C
   #define USART_ENABLE_TRANSMITTER		TXEN0
   #define USART_ENABLE_RECEIVER		RXEN0
   #define USART_READY_TO_TRANSMIT		UDRE0
   #define USART_TRANSMIT_COMPLETE		TXC0
   #define USART_RECEIVE_COMPLETE		RXC0
   #define USART_DATA_REG				UDR0
   #define USART_STOP_BIT_SELECT		USBS0
   #define USART_CHARACTER_SIZE			UCSZ00

#else
   #error "no USART definition for MCU"
#endif

/*****************************************************
	USART function declarations	 
******************************************************/
static void Initialization();
static void USARTInit();
static void sendByte( uint8_t );
static uint8_t receiveByte( void );
void sendStringPROGMEM(const char *); 

#if defined(Butterfly)
void OSCCAL_calibration(void);
void Delay(unsigned int) ;
#endif
