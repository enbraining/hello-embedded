#include <wiringPi.h>
#include <softPwm.h>

int main()
{
  int light = 1, count = 0;

  wiringPiSetup();

  pinMode(2, OUTPUT);

  softPwmCreate(2, 0, 100);

  while(1)
  {
    softPwmWrite(2, light);
    delay(50);
    
    if(count < 100)
    {
        light++;
        count++;
    } else if(count >= 100) light--;

    if(light == 0)
    {
      count = 0;
      break;
    }
  }
}
