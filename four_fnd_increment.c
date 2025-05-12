#include <stdio.h>
#include <wiringPi.h>

#define SW1 0

int num[10] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
int disp[4] = {5, 6, 7, 8};
int data[4] = {24, 23, 22, 21};
int DIGIT[4] = {4, 5, 6, 26};

int cnt = 0;
int s1 = 0, s2 = 0;

void SW1_handle(void) {
    s1 = 1;
}

int main(void) {
    wiringPiSetup();
    pinMode(SW1, INPUT);

    for (int i = 0; i < 4; i++) {
        pinMode(data[i], OUTPUT);
        pinMode(DIGIT[i], OUTPUT);
        digitalWrite(data[i], HIGH);
        digitalWrite(DIGIT[i], LOW);
    }

    wiringPiISR(SW1, INT_EDGE_RISING, &SW1_handle);

    while (1) {
        cnt++;
        if (s1 == 1) {
            cnt++;
            s1 = 0;
        } else if (s2 == 1) {
            cnt--;
            s2 = 0;
        }
        if (cnt < 0) cnt = 0;
        cnt = cnt % 10000;

        disp[3] = cnt % 10;
        disp[2] = (cnt / 10) % 10;
        disp[1] = (cnt / 100) % 10;
        disp[0] = (cnt / 1000) % 10;

        for (int k = 0; k < 20; k++) {
            for (int i = 0; i < 4; i++) {
                digitalWrite(DIGIT[i], 1);
                for (int j = 0; j < 4; j++) {
                    digitalWrite(data[j], (num[disp[i]] >> (3 - j)) & 0x01);
                }
                delay(1);
                digitalWrite(DIGIT[i], 0);
            }
        }
    }

    return 0;
}
