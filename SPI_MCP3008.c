// SPI_MCP3008.c
//
// Shows how to interface with SPI to transfer & receive byte3 to an SPI device
// Interface Raspberry Pi to MCP3008 using SPI communication.
//
// BCM2835 Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

// Program code for MCP3008 analog to digital converter by D. Robinson

#include <bcm2835.h>
#include <stdio.h>

// Channel configuration set to single ended.
const unsigned char write_channum[8] = {                         
     0x80, 0x90, 0xA0, 0xB0,  
     0xC0, 0xD0, 0xE0, 0xF0       
};

// Function prototype
void print_data(int *show_nums);

int main(int argc, char **argv)
{
	int idx = 0;
	char trans_data[3];
	trans_data[0] = 0x01;
	trans_data[1] = 0x80;
	trans_data[3] = 0x00;
	char rec_data[3] = { 0x00, 0x00, 0x00 };
	int adc_val;
	int adc_values[8];

	// If you call this, it will not actually access the GPIO
	// Use for testing
	// bcm2835_set_debug(1);

	if (!bcm2835_init())
	{
		printf("bcm2835_init failed. Are you running as root??\n");
		return 1;
	}

	if (!bcm2835_spi_begin())
	{
		printf("bcm2835_spi_begin failed. Are you running as root??\n");
		return 1;
	}
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

	//Read the 8 analog channels.
	printf("\nGathering data ..... please wait\n");
	for (idx = 0; idx < 8; idx++)
	{
		trans_data[1] = write_channum[idx];		// set up channel to read
		bcm2835_spi_transfernb(trans_data, rec_data, 3);
		adc_val = ((rec_data[1] & 3) << 8) + rec_data[2];		// adc value
		adc_values[idx] = adc_val;		// store read values
		bcm2835_delay(100);		// delay for 100 msec.
	}
	
    bcm2835_spi_end();	// end communication
    bcm2835_close();	// close SPI port

	print_data(adc_values);		// call print data function
    return 0;
}

// Function definition to display data
void print_data(int *show_nums)
{
	int inc;
		for(inc = 0; inc < 8; inc++)
	{
		printf("Channel %d: %04d  ", inc, show_nums[inc]);
		if(inc == 3) printf("\n");
	}
		printf("\n");
}
