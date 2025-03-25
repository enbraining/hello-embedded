#include <stdio.h>
#include <wiringPi.h>

int main()
{
	const int button_pin = 3;
	const int led_pin = 0;

	wiringPiSetup();

	pinMode(button_pin, INPUT);
	pinMode(led_pin, OUTPUT);
	pullUpDnControl(button_pin, PUD_UP);

	while(1)
	{	
		while(digitalRead(button_pin) == HIGH)
		{
			digitalWrite(led_pin, HIGH);
		}
		digitalWrite(led_pin, LOW);
	}
}
