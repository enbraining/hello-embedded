#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRE = 0xff;
  PORTE = 0b00000001;

  while(1)
  {
    PORTE = ~PORTE;
    _delay_ms(500);
  }

  return 0;
}
