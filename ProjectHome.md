**I strongly encourage collaboration. If you want to participate please contact me.**

**Some of the materials in this repository have extra documentation located at
http://smileymicros.com/blog**

# avrtoolbox Design Philosophy #

**avrtoolbox** is a collection of open source educational tools for learning about and using Atmel AVR (8-bit) microcontrollers with the standard Atmel AVR Toolchain: AVRStudio/WinAVR/avrdude.

Because the AVR architecture varies among sub-families, it would be very difficult to create compiled hardware libraries that could be run on all possible AVR variants. Our initial approach will be to create a single source code repository for three different AVRs available on inexpensive development boards in order to demonstrate concepts and leave it to the users to follow the methods shown to add additional devices as needed.

The two AVRs we will use are the ATmega169 and ATmega328; and we will test our tools on two development boards: Butterfly (ATmega169) and Arduino Duemilanove or Uno Boards (ATmega328).

For the Arduino board, this system does not use the Arduino IDE nor is it compatible with the existing Arduino libraries.

**The following are intents and open to discussion**
The software is grouped into directories that contain the function modules library and a tester module for each group. For example, there is an SPI library directory and an SPI\_tester.c module. Each tested module is collected into a library specific to one of the three development boards: libavrtools169.a, libavrtools328.a libavrtools644.a.

Library documentation is generated using Doxygen and is located in the \doc directory.

# avrtoolbox Libraries: #
  * **elementary** - High level simple functions similar to those in Arduino or PBasic.
  * **general** – Useful embedded system software that is not AVR specific.
  * **driver** – AVR specific software.
  * **board** – Custom software for development boards such as the Butterfly or BeAVR.
  * **testers** - Test software for each library.
## Other tools: ##
  * **avr\_applications** - Complete programs for the AVR.
  * **pc\_applications** - Tools for the PC written in C#.
  * **doxygen\_documentation**


---


---


# On getting help. #
I think it benefits the community to keep all questions public. I have chosen www.AVRFeaks.net to respond to questions so that if someone else has the same question they might find it by searching that forum.

This also benefits you since there are people available 24/7 who might answer your question well before I even see it.

After reading ‘Newbie? Start here!’: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=70673 then please start a thread with avrtoolbox in the title. I repeat: make sure avrtoolbox is in the title or I will probably miss it.

Also be aware that this is the Internet and there are trolls on AVRFreaks who will try to intimidate you or will provide incorrect advice - ignore them, they don't deserve your time - caveat emptor is the watchword.

Items with <> are in beta release, items with >< will follow as time allows.

**Tools planned:**
  * **elementary**
    * <>Serial Communications
    * <>Digital I/O
    * ><Analog I/O
    * ><Advanced I/O
    * ><Time
    * ><External Interrupts
  * **general**
    * <>fifo
    * <>datetime
    * <>DataFlash
    * <>edubootavr
    * ><boot500
    * <>Command Interpreter
  * **driver**
    * **peripheral**
      * <>uart
      * <>spi
      * <>eeprom
      * ><adc
      * ><pwm
      * ><timer
    * **software**
      * <>spi
      * ><i2c
      * ><DAC pwm
      * ><DAC resistor ladder
    * **external\_hardware**
      * <>lcd\_hd44780
      * <>nav\_button
      * ><ir\_remote
      * ><h\_bridge
      * ><rtc
      * ><radio
  * **board**
    * **butterfly**
      * <>bootloader
      * <>joystick
      * <>lcd
      * <>menu
    * **arduino\_328**
      * ><bootloader
    * **beavr\_644**
      * ><bootloader
  * **testers**
    * <>lcd\_hd44780
    * <>nav\_buttons
    * <>digitalio
    * <>serial
    * <>usart
    * <>spi
    * <>uart
    * <>ring buffer
    * <>eeprom
    * <>program\_memory
    * <>dataflash
    * <>datetime
    * <>butterfly\_joystick
    * <>butterfly\_lcd
    * <>butterfly\_menu
  * **avr\_applicatons**
    * <>chaser\_lights
    * <>command\_line\_demo
  * **pc\_applicatons**
    * <>developers\_terminal
    * <>simple\_terminal
    * <>butter\_up - GUI for using avrdude with the Butterfly.
    * <>ard\_up - GUI for using avrdude with the Arduino 328 board.
  * **avr\_pc\_applications**
    * <>arduino\_voltmeter - Arduino and PC GUI