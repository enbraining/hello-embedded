#include <wiringPi.h>
#include <stdio.h>

#define LED 0
#define BUTTON 1

int main()
{
  printf("Raspberry Pi blink\n");
  
  wiringPiSetup();
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pullUpDnControl(BUTTON, PUD_UP);
  
  while(1)
  {
      if(digitalRead(BUTTON) == LOW){
        digitalWrite(LED, HIGH);
      } else {
        digitalWrite(LED, LOW);
      }
  }
  
  return 0;
}
