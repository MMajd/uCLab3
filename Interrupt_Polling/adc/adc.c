/*
 * adc.c
 *
 * Created: 4/22/2018 11:47:28 AM
 *  Author: tornado_win
 */ 

#include "adc.h"
#include <avr/io.h>

void adc_init(unsigned char flag_8_16)
	// ADC Enable and prescaler of 8
	// start single convertion, by writing �1? to ADSC
	// wait for conversion to complete, ADSC becomes �0? again, till then, run loop continuously
	// start single convertion, by writing �1? to ADSC
	// wait for conversion to complete, ADSC becomes �0? again, till then, run loop continuously