#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_COMP_vect)
{
	PORTB = ~PORTB;
}

int main()
{
	DDRA = 0xff;
	DDRB = 0xff;
	
	PORTA = 0xff;
	
	// 부저로 들어가는 전압
	TCCR0 |= (1 << WGM01) | (1 << CS00) | (0 << CS01) | (1 << CS02);
	TIMSK |= (1 << OCIE0) | (1 << TOIE0);
	TCNT0 = 0;
	OCR0 = 65;

	SREG = 0x80;
	
	// 부저에서 나오는 전압                                                                             
	while(1)
	{
		PORTA = 0xff;
		_delay_ms(600);
		PORTA = 0x00;
		_delay_ms(400);
	}
}
