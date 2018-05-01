/*
 * adc.c
 *
 * Created: 4/22/2018 11:47:28 AM
 *  Author: tornado_win
 */ 

#include "adc.h"
#include <avr/io.h>

void adc_init(unsigned char flag_8_16){	if (flag_8_16 == 0) {		// AREF = Avcc .. Internal		ADMUX = (1<<REFS0) | (1<<ADLAR);		} else {		// AREF = Avcc .. Internal		ADMUX = (1<<REFS0);	}
	// ADC Enable and prescaler of 8	// 1000000 / 8 = 125000	ADCSRA = (1<<ADEN)| (1<<ADPS1)|(1<<ADPS0);}unsigned int adc_read(unsigned char ch){	// select the corresponding channel 0~7	ADMUX |= ch;
	// start single convertion, by writing ’1? to ADSC	ADCSRA |= (1<<ADSC);
	// wait for conversion to complete, ADSC becomes ’0? again, till then, run loop continuously	while(ADCSRA & (1<<ADSC));	return ADC;}unsigned char adc_read_8_bit(unsigned char ch){	// select the corresponding channel 0~7	ADMUX |= ch;
	// start single convertion, by writing ’1? to ADSC	ADCSRA |= (1<<ADSC);
	// wait for conversion to complete, ADSC becomes ’0? again, till then, run loop continuously	while(ADCSRA & (1<<ADSC));	return ADCH;}