#include <stdio.h>
#include <wiringPi.h>

int main(void) {
    int num[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
    int disp[4]={5,6,7,8};
    int data[4] = {24,23,22,21};
    int digit[4] = {4,5,6,26};

    wiringPiSetup();
    
    for(int i=0; i<4; i++) {
        pinMode(data[i],OUTPUT);
        pinMode(digit[i],OUTPUT);
        digitalWrite(data[i], HIGH);
        digitalWrite(digit[i], LOW);
    }
  
    while(1) {
        for(int i=0; i<4; i++) {
            digitalWrite(digit[i],1);
            for(int j=0; j<4; j++)
                digitalWrite(data[j],(num[disp[i]]>>(3-j) & 0x01));
            delay(5);
            digitalWrite(digit[i],0);
        }
    }
}
