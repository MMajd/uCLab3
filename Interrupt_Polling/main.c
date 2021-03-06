/*
 * THREE MODES PROGRAM 
 *
 * Created: 4/29/2018 4:01:49 PM
 * Author : Muhammad Abu al-Majd 
 */ 

/* CPU Freq */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "adc/adc.h" 


#define OUTPUT_PORT(_PORT)			_PORT = 0xFF
#define INPUT_PORT(_PORT)			_PORT = 0x00

#define ENBLE_PULLUP(_PORT)			_PORT = 0xFF


#define SET_BIT(ADDR, BIT)			ADDR |=	(1<<BIT)
#define RESET_BIT(ADDR, BIT)		ADDR &= ~(1<<BIT)
#define TOGGLE_BIT(ADDR, BIT)		ADDR ^= (1<<BIT)
#define READ_BIT(ADDR, BIT)			((ADDR & (1<<BIT))>>BIT)
#define CHK_PIN_HIGH(_PORT, _PIN)	(_PORT & (1<<_PIN))
#define CHK_PIN_LOW(_PORT, _PIN)	!(_PORT & (1<<_PIN))

/* MODE_ONE PORTB will be lighten from b0 up to b7 and restart again*/ 
#define MODE_ONE		1 
/* MODE_ONE PORTB will be lighten from b7 down to b0 and restart again*/ 
#define MODE_TWO		2 
/* MODE_ONE PORTB will be lighten according to ADC input*/ 
#define MODE_THREE		3

int mode_flag = MODE_ONE; 
unsigned char adc_r_8 = 0;

int main(void)
{
	//set all pins in port b to output
	OUTPUT_PORT(DDRB); 
			
	//input pin 
	RESET_BIT(DDRD, PORTD4);

	//choosing one mode of interrupts int pins 4 modes 
	//Low level for INT0
	//portd2
	RESET_BIT(EICRA, ISC00);
	RESET_BIT(EICRA, ISC01); 

	//enabling interrupt request and global interrupt flag 
	SET_BIT(EIMSK, INT0);
	sei(); 

	adc_init(0);

	int leds = 0;
	int counter = 0; 
		
	unsigned char adc_r_8 = 0;

    while (1) 
    {
		//PIND4 here is active low 
		if(CHK_PIN_LOW(PIND, PIND4)) {
			if(mode_flag < MODE_THREE) {
				// toggle the mode from mode 2 to 1, or vise versa
				if(mode_flag == MODE_ONE)  { 
					mode_flag = MODE_TWO;
					leds = 0;
					counter = -1;  					
				} 
				else { 
					mode_flag = MODE_ONE;
					leds = 0;
					counter = 8;  
				} 
				
			}
			else {
				//change mode
				mode_flag = MODE_ONE;
				leds = 0;
				counter = 8; 
			}
		}

		if(mode_flag == MODE_ONE) {
			if(counter > 7) {
				leds = 0;
				counter = -1;
			}
			SET_BIT(leds, counter++);
			PORTB = leds; 
			_delay_ms(500); 
		}
		else if(mode_flag == MODE_TWO) {
			if(counter < 0) {
				leds = 0; 
				counter = 8;
			}
			SET_BIT(leds, counter--);
			PORTB = leds;
			_delay_ms(500); 
		}
		else {
			adc_r_8 = adc_read_8_bit(0);
			PORTB = adc_r_8;
			_delay_ms(500); 
		}
    } // end of while loop 
}

ISR(INT0_vect)
{
	//disable interrupts 
	cli(); 

	if (mode_flag != MODE_THREE) {
		PORTB = 0; 
		_delay_ms(500); 
	}
	
	adc_r_8 = adc_read_8_bit(0);
	PORTB = adc_r_8;
	 
	_delay_ms(500); 
	mode_flag = MODE_THREE; 
	//enable interrupts
	sei(); 
}