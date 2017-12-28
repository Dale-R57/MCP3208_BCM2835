MCP3208 analog to digital converter to Raspberry Pi (3B used for this program).  Analog inputs are configured for single ended.
Written in C, using the BCM2835 Library (Mike McCauley)

Hardware
Raspberry Pi ----------> MCP3208 (pin #)
3.3V ------------------> VDD (16)
3.3V ------------------> VREF (15)
GND -------------------> AGND (14)
SPIO_CLK --------------> CLK (13)
SPIO_MISO -------------> DOUT (12)
SPIO_MOSI -------------> DIN (11)
SPI_CE0_N -------------> CS (10)
GND -------------------> DGND (9)

MCP3208 analog input channels 0 to 7 are connected to the MCP3208 pins 1 through 8 respectively.

Software
- download and install the BCM2835 library.
- Geany program editor on the Raspberry Pi was used as the C compiler.
- Within Geany, under Build, Set build commands, add
-lbcm2835 to the end of the 'compile' and 'build' statements.
- compile and build program.
- open terminal program window, navigate to the folder where the compiled file is located, type sudo ./<filename> <enter>.

Results
- the program will display the channel data in a 2 line format, then end.  The program may be easily modified to continually update the data.
