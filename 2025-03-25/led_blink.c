#include <stdio.h>
#include <wiringPi.h>

int main()
{
        int led_1 = 0, led_2 = 1, led_3 = 2;

        wiringPiSetup();

        pinMode(led_1, OUTPUT);
        pinMode(led_2, OUTPUT);
        pinMode(led_3, OUTPUT);

        while(1)
        {
                digitalWrite(led_1, HIGH);
                digitalWrite(led_2, LOW);
                delayMicroseconds(100000);
                digitalWrite(led_1, LOW);
                digitalWrite(led_2, HIGH);
                delayMicroseconds(100000);
        }
}
