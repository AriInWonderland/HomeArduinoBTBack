/*
    I have to add a way for the serial to be decoded from base64 to decimal
*/
#include <SoftwareSerial.h>

#define LED_PIN 3
#define BT_STATE 4

#define LED 3

#define MAX 256

SoftwareSerial BT(5, 6); //RX | TX
int flag[MAX], msg[MAX], temp;

int length(int array[]){
    int i;
    for(i=0; array[i] != '\0'; i++){
        ; 
    }
    return i;
}

int decode_device(int coded[], char decoded[]){
    //dependiendo el length del array es su valor
    int l = length(coded);
    if(l<3)
        return -1;
    //Serial.print("Lenght: ");
    //Serial.println(l);
    switch(l){
        case 3:
            strcpy(decoded, "LED");
            return 0;
            break;
        default:
            strcpy(decoded, "Invalid Device"); 
            return 0;
            break;
    }
}

int decode_value(int coded[]){
    Serial.println("Decoding value");
}

void setup(){
    Serial.begin(38400);
    BT.begin(38400);
    pinMode(LED, OUTPUT);
    Serial.println("Ready!!!");
}

void loop(){
    int i=0, j, buffer[MAX];
    char decoded[25];

    for(i=0; i<=24; i++)
        decoded[i]=0;

    if(BT.available()){
        for(i=0;i<254; i++){
            temp = BT.read();
            flag[i] = temp;
        }
        for(i=0, j=0; i<255; i++){
            if(flag[i] > 0){
                msg[j] = flag[i];
                j++;
            } else {
                continue;
            }
        }
        msg[j] = 777;
        for(i=0; msg[i] != 777; i++){
            buffer[i] = msg[i];
        }
        buffer[i++] = '\0';
        //for(i=0; i!='\0';i++)
            //Serial.println(buffer[i]);
        //este decoded accede al 'ambiente' del dispositivo
        //o sea lo que reciva lo decodifica y lo escribe
        
        decode_device(buffer, decoded);
        if(strcmp(decoded, "LED")==0){
            Serial.println("LED");
            //tomar todo pero ddespues al momento de contar tiene que ser -2 
            //port el paquete ese que se manda extra
            //flag = BT.read()
            if(BT.available()){
            for(i=0;i<254; i++){
                temp = BT.read();
                flag[i] = temp;
            }
            for(i=0, j=0; i<255; i++){
                if(flag[i] > 0){
                    msg[j] = flag[i];
                    j++;
                } else {
                    continue;
                }
            }
            msg[j] = 777;
            for(i=0; msg[i] != 777; i++)
                buffer[i] = msg[i];
            
            buffer[i++] = '\0';           //BT.read()
            for(i=2;buffer[i]!='\0'; i++)
                Serial.println(buffer[i]);
            int l = length(buffer) - 2;
            Serial.print("l = ");
            Serial.println(l);
            switch(l){
                case 4:
                    Serial.println("ON");
                    digitalWrite(LED_PIN, "HIGH");
                    delay(5000);
                    Serial.println("OFF");
                    //digitalWrite(LED_PIN, "LOW");
                    analogWrite(LED_PIN, 0);
                    break;
                default:
                    Serial.println("non");
                    break;
            }
            }
        }
    }
}
