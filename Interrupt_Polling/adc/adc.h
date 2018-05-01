/*
 * adc.h
 *
 * Created: 4/22/2018 11:47:07 AM
 *  Author: tornado_win
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(unsigned char flag_8_16);
unsigned int adc_read(unsigned char ch);
unsigned char adc_read_8_bit(unsigned char ch);
#endif /* ADC_H_ */

