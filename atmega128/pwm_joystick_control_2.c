/*
조이스틱 가변저항의 값과 서보모터 회전이 완전히 매칭되지 않지만, 돌아가긴 한다.
*/

#define F_CPU 16000000UL
#define ADC_VREF_TYPE 0x40

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

char receive_buf = 0;

ISR(USART0_RX_vect)
{
	receive_buf = UDR0;
}

void usart0_init();
void timer1_init();
void usart0_char(char data);
void usart0_string(char *str);
unsigned int read_adc(unsigned char adc_input);
unsigned int read_adc_safely(unsigned char adc_input);

int main()
{
	DDRA = 0xff;
	DDRB = 0xff;
	
	usart0_init();
	timer1_init();
	
	ADMUX = ADC_VREF_TYPE;
	ADCSRA = 0x86;
	
	SREG = 0x80;
	
	while(1)
	{
		if(receive_buf)
		{
			usart0_char(receive_buf);
			receive_buf = 0;
		}
		
		int adc_result_1 = read_adc_safely(0);
		int adc_result_2 = read_adc_safely(1);
		
		OCR1A = adc_result_1;
		
		char buf[100];
		sprintf(buf, "%d\n", adc_result_1 / 5);
		usart0_string(buf);
		
		_delay_ms(10);
	}
}

void usart0_init()
{
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	
	UBRR0H = 0;
	UBRR0L = 103;
}

void usart0_char(char data)
{
	while(!(UCSR0A & 0x20));
	UDR0 = data;
}

void usart0_string(char *str)
{
	while(*str)
	usart0_char(*str++);
}

unsigned int read_adc(unsigned char adc_input)
{
	ADMUX = adc_input | ADC_VREF_TYPE;
	
	_delay_us(10);
	
	ADCSRA |= 0x40;
	while((ADCSRA & 0x10) == 0x00);
	ADCSRA |= 0x10;
	
	return ADCW;
}

unsigned int read_adc_safely(unsigned char adc_input)
{
	int result = 0;
		
	for(int i = 0; i < 10; i++)
	{
		result += read_adc(adc_input);
		_delay_ms(5);	
	}
	
	return result / 10;
}

void timer1_init()
{
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
	ICR1 = 4999;
	OCR1A = 374;
}
