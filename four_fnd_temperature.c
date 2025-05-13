#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdint.h>

#define SW1 0
#define MAXTIMINGS 85
#define DHTPIN 29

int dht11_dat[5] = { 0, 0, 0, 0, 0 };

int num[10] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
int disp[4] = {5, 6, 7, 8};
int data[4] = {24, 23, 22, 21};
int DIGIT[4] = {4, 5, 6, 26};

int cnt = 0;
int s1 = 0, s2 = 0;

void read_dht11_dat();

int main(void) {
    wiringPiSetup();
    pinMode(SW1, INPUT);

    for (int i = 0; i < 4; i++) {
        pinMode(data[i], OUTPUT);
        pinMode(DIGIT[i], OUTPUT);
        digitalWrite(data[i], HIGH);
        digitalWrite(DIGIT[i], LOW);
    }

    while (1) {
        read_dht11_dat();

        if(dht11_dat[0] > 0 && dht11_dat[2] > 0){
            disp[0] = (dht11_dat[0] / 10) % 10;
            disp[1] = dht11_dat[0] % 10;
            disp[2] = (dht11_dat[2] / 10) % 10;
            disp[3] = dht11_dat[2] % 10;
        }

        for (int i = 0; i < 4; i++) {
            digitalWrite(DIGIT[i], 1);
            for (int j = 0; j < 4; j++) {
                digitalWrite(data[j], (num[disp[i]] >> (3 - j)) & 0x01);
            }
            delay(1);
            digitalWrite(DIGIT[i], 0);
        }
    }

    return 0;
}

void read_dht11_dat(){
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    
    uint8_t j = 0, i = 0;
    float f; /*fahrenheit*/
    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4]= 0;
    /* pull pin down for 18 milliseconds */
    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);
    /*then pull it up for 40 microseconds */
    digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40);
    /*prepare to read the pin*/
    pinMode(DHTPIN, INPUT);
    /*detect change and read data*/
    for (i =0 ; i < MAXTIMINGS; i++) {
        counter = 0;
        while(digitalRead(DHTPIN)==laststate) {
            counter++;
            delayMicroseconds(1);
            if(counter==85) {
                break;
            }
        }
        laststate = digitalRead(DHTPIN);
        if(counter==85)
            break;
        /*ignore first 3 transitions*/
        if((i>=4) && (i%2==0)) {
            /*shove each bit into the storage bytes*/
            dht11_dat[j/8] <<= 1;
            if(counter > 16)
                dht11_dat[j/8] |= 1;
            j++;
        }
    }
    /*
    *check we read 40 bits(8bits x 5) + verify checksum in the last byte
    *print it out if data is goo
    */
    if((j >= 40) && (dht11_dat[4] == (dht11_dat[0] + dht11_dat[1] + dht11_dat[2]+ (dht11_dat[3] & 0xFF)))) {
        f = dht11_dat[2] * 9. / 5. +32;
        printf("Humidity = %d.%d %% Temperature = %d.%d *C (%.1f*F)\n", dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f);
    }
    else {
        printf("Data not good, skip\n");
    }
}
