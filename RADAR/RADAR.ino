#include <radar.h>

#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(11, 10); // RX, TX
    #define Serial1 SSerial
#endif
#define MESSAGE_HEAD 0x55
int data[14] = { 0 };
int MSG;
int Situation_action;
radar RADAR;
byte radarData[14] = {0}; // Array to store radar data


void setup() {
    Serial1.begin(9600);  // Radar serial communication
    Serial.begin(9600);   // Serial monitor communication
    Serial.println("Radar Initialized!");
    
}


void loop() {
    MSG = Serial1.read();
    for(int i=0; i<128;i++){
      MSG = Serial1.read();
      Serial.print(MSG, HEX);
    }

    
    Serial.println();
    //   if(MSG == MESSAGE_HEAD){

    //     for (int i = 0; i < 14; i++) {
    //             while (!Serial1.available()); // Wait for each byte
    //             data[i] = Serial1.read();
    //         }
    //     }

    //     if (MSG == MESSAGE_HEAD){
    //     Situation_action = RADAR.Situation_judgment(data[5], data[6], data[7], data[8], data[9]);   //situation function
    //       if (Situation_action == 1){
    //         Serial.println("radar said nobody");
    //       }
    //       if (Situation_action == 2){
    //         Serial.println("radar said somebody move");
    //       }
    //       if (Situation_action == 3){
    //         Serial.println("radar said somebody stop");
    //       }
    //       if (Situation_action == 4){
    //         Serial.println("radar said no move");
    //       }
    //       if (Situation_action == 5){
    //         Serial.println("radar said somebody close");
    //       }
    //       if (Situation_action == 6){
    //         Serial.println("radar said somebody away");
    //       } 
    //     }
}

 
