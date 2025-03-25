#include <stdio.h>
#include <wiringPi.h>

void toggleLed(int index);

int main()
{
        int led_1 = 0, led_2 = 1, led_3 = 2;
	int index = 0;

        wiringPiSetup();

        pinMode(led_1, OUTPUT);
        pinMode(led_2, OUTPUT);
        pinMode(led_3, OUTPUT);

        while(1)
        {
		if(index >= 3) index = 0;
                toggleLed(index++);
                delayMicroseconds(100000);
        }
}

void toggleLed(int index)
{
        for(int i = 0; i <= 2; i++)
        {
                if(i == index) digitalWrite(i, HIGH);
                else digitalWrite(i, LOW);
        }
}
