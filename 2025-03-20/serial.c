#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

char receive_buf = 0;

void usart0_init(){
    UCSR0A=0x00;
    UCSR0B=0x98;
    UCSR0C=0x06;
    UBRR0H=0;
    UBRR0L=8;
    sei();
}

void USART0_char(char data) {
    while(!(UCSR0A&0x20));
    UDR0 = data;
}

void USART0_str(char *str)
{
    while (*str)
    USART0_char(*str++);
}

int main(void) {
    int result = 0;
    char calc = NULL;

    usart0_init();
    while(1) {
        if(receive_buf) {
            if(receive_buf >= '0' && receive_buf <= '9'){
                if(calc == NULL || calc == '+') result += receive_buf - 48;
                else if(calc == '-') result -= receive_buf - 48;
                else if(calc == '*') result *= receive_buf - 48;
                else if(calc == '/') result /= receive_buf - 48;
            } else if (receive_buf == '+' || receive_buf == '-' || receive_buf == '*' || receive_buf == '/'){
                calc = receive_buf;
            } else if (receive_buf == '?'){
                char output[10];
                sprintf(output, "%d", result);
                USART0_str(output);
                USART0_str("\n");
                
                calc = NULL;
                result = 0;
            }
            
            receive_buf = 0;
        }
    }
}

ISR(USART0_RX_vect)
{
    receive_buf = UDR0;
}
