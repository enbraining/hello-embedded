#include <wiringPi.h>
#include <stdio.h>

#define LED 0
#define BUTTON 1

int main()
{
  volatile int is_toggle = 0;
  
  wiringPiSetup();
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pullUpDnControl(BUTTON, PUD_UP);
  
  while(1)
  {
      while(digitalRead(BUTTON) == LOW){
        is_toggle = !is_toggle;
        while(digitalRead(BUTTON) == LOW);
      } 
              
      digitalWrite(LED, is_toggle);
  }
  
  return 0;
}
