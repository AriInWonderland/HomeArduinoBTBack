/*
    Ok, I can change between hex and decimal using the terminal app,
    idk how it works with react native. BUT the serial is decimal
    This means that if I send a hex 41 the serial will interpret a 
    decimal 65. So if I use ascii hex I can detect decimal ASCII

    Yeah I can just send ASCII and detect it as decimal ASCII,
    I think I can (char)flag to print the char instead of the decimal,
    BUT this goes byte by byte and it's kinda useless
*/
#include <SoftwareSerial.h>

#define LED 3
#define BT_STATE 4

SoftwareSerial BT(5, 6); //RX | TX
int flag = 0;

void setup(){
    Serial.begin(9600);
    BT.begin(9600);
    pinMode(LED, OUTPUT);
    Serial.println("Ready!!!");
}

void loop(){
    if(BT.available())
        flag = BT.read();

    if(flag != 13 && flag != 10){ //CHANGE THIS LATER THIS IS BECAUSE OF THE 
        switch(flag){                          //BT TERMINAL APP WHICH SENDS EXTRA STUFF
            case 'A':
                digitalWrite(LED, LOW);
                break;
            case 'a':
                digitalWrite(LED, HIGH);
                break;
            default:
                break;
        }
    }
}
