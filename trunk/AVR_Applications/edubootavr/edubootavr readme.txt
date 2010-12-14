edubootavr is the source code for the AVR109 type bootloader presented in 
Nuts&Volts Smiley's Workshop 27 AVR Memory Part 5 Bootloaders.

The initial specification for the bootloader is:

  # Fits in the 1024 byte boot section.
  # Uses #defines to make it usable for the ATmega328, ATmega644, and ATmega169.
  # Uses Doxygen for comments.
  # Has an AVRStudio/WinAVR project.5. Uploads using avrdude.
  # Has hex releases for the following platforms:
    * Arduino Duemilanove Hardware
    * AVR Butterfly
    * ATmega644 16MHz on a breadboard (TODO: LINK TO BEAVR).
  # License: New BSD8. Version Control: SVN
  # In cases where ‘education’ seems to conflict with ‘efficiency’ special efforts 
  should be made to educate the user about the complexity required for efficiency. 
  By this I mean that the comment might show the conceptually clear way to do something, 
  then explain the less clear algorithm that has been found to be more efficient.