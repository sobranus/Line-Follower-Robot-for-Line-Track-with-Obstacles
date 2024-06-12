#include <avr/io.h>
#incude <util/delay.h>

uint16_t result[6];

void init_output(void) {
	DDRD |= _BV(PD0) | _BV(PD1) | _BV(PD2) | _BV(PD3) | _BV(PD4) | _BV(PD5);
}

void init_adc(void) {
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);
}

uint16_t adc_read(uint8_t adc_channel) {
	ADMUX = (ADMUX & 0xF8) | (adc_channel & 0x07);
	ADCSRA |= (1 <<ADSC);
	
	while (ADCSRA & (1 << ADSC)) {
	
	return ADC;
}

int main(void) {
	init_output();
	init_adc();
	
	PORTD |= _BV(PD2);
	PORTD &= ~_BV(PD1);
	PORTD |= _BV(PD4);
	PORTD &= ~_BV(PD3);
	
	while (1) {
		for (int i = 0; i < 6; i++) {
			result[i] = adc_read(i);
		}
		
		if (result[1] >= 300 || result[0] >= 300) {
			PORTD |= _BV(PD5);
			PORTD &= ~_BV(PD0);
		} else if (result[4] >= 400 || result[5] >= 800) {
			PORTD |= _BV(PD0);
			PORTD &= ~_BV(PD5);
		}
			
		} else {
			PORTD |= _BV(PD0);
			PORTD |= _BV(PD5);
		}
		_delay_ms(100);
	}
	return 0;
}