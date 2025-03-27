#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xff;
	DDRB = 0xff;
	
	PORTA = 0xff;
	
	// 부저로 들어가는 전압
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00) | (0 << CS01) | (1 << CS02);
	TIMSK |= (1 << OCIE0) | (1 << TOIE0);
	OCR0 = 128;
	
	// 부저에서 나오는 전압
	
	                                                                                     
	while(1)
	{
		PORTA = 0xff;
		_delay_ms(400);
		PORTA = 0x00;
		_delay_ms(200);
	}
}
