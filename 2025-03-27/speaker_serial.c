#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile char receive_buf = 0;
volatile int level = 65;

// USART setting
void usart0_init(){
	UCSR0A=0x00;
	UCSR0B=0x98;
	UCSR0C=0x06;
	UBRR0H=0;
	UBRR0L=8;
	sei();
}

// USART 문자 출력
void USART0_char(char data) {
	while(!(UCSR0A&0x20));
	UDR0 = data;
}

// USART 문자열 출력
void USART0_str(char *str)
{
	while (*str)
	USART0_char(*str++);
}

int main()
{
	usart0_init();
	
	// 출력 설정
	DDRA = 0xff;
	DDRB = 0xff;
	
	// CTC 모드, 분주 설정
	TCCR0 |= (1 << WGM01) | (1 << CS00) | (0 << CS01) | (1 << CS02);
	TIMSK |= (1 << OCIE0) | (1 << TOIE0);
	
	// 기초값과 비교값
	TCNT0 = 0;
	OCR0 = level;
	
	// 외부 인터럽트 허용
	SREG = 0x80;
	 
	while(1){}
}

// 타이머 비교 인터럽트
ISR(TIMER0_COMP_vect)
{
	PORTB = ~PORTB;
}

ISR(USART0_RX_vect)
{
	receive_buf = UDR0;
	
	if(receive_buf >= '1' && receive_buf <= '9')
	{
		OCR0 = 60 + (receive_buf - 48) * 10;
		PORTA = 0xff;
		_delay_ms(50);
		PORTA = 0x00;
	}
}
