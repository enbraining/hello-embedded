#include <wiringPi.h>
#include <stdio.h>

#define BUTTON 0
#define LED_1 1
#define LED_2 2
#define LED_3 3

volatile int led_index = 1;

void button_interrupt()
{
  if(led_index >= 3) led_index = 0;
  led_index++;
}

int main()
{
  wiringPiSetup();
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(BUTTON, INPUT);
  pullUpDnControl(BUTTON, PUD_UP); 

  if(wiringPiISR(BUTTON, INT_EDGE_RISING, &button_interrupt) < 0)
  {
        printf("Interrupt failed\n"); 
  }
  
  while(1)
  {
      for(int i = 1; i <= 3; i++)
      {
        digitalWrite(i, i == led_index);
      }
  }
  
  return 0;
}
