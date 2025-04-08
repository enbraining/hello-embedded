#include <stdio.h>
#include <wiringPi.h>

int main()
{
  int data[4] = { 24, 23, 22, 21 };
  int digit[4] = { 4, 5, 6, 26 };

  wiringPiSetup();

  for(int i = 0; i < 4; i++)
  {
    pinMode(data[i], OUTPUT);
    pinMode(digit[i], OUTPUT);
    digitalWrite(data[i], LOW);
    digitalWrite(digit[i], LOW);
  }

  while(1)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(26, HIGH);

    digitalWrite(24, LOW);
    digitalWrite(23, LOW);
    digitalWrite(22, LOW);
    digitalWrite(21, LOW);
  }
}
