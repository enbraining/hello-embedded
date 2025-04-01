#include <wiringPi.h>
#include <stdio.h>

#define LED 0
#define BUTTON 1

volatile int is_toggle = 0;

void button_interrupt()
{
  is_toggle = !is_toggle;
}

int main()
{
  wiringPiSetup();
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pullUpDnControl(BUTTON, PUD_UP);

  if(wiringPiISR(BUTTON, INT_EDGE_RISING, &button_interrupt) < 0)
  {
        printf("Interrupt failed\n"); 
  }
  
  while(1)
  {
      if(is_toggle) digitalWrite(LED, HIGH);
      else digitalWrite(LED, LOW);
  }
  
  return 0;
}
