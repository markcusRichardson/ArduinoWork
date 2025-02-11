#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(10, 11); // RX, TX

void setup() {
    Serial.begin(9600);         // For Serial Monitor
    gpsSerial.begin(9600);      // For GPS module
    Serial.println("GPS module started...");
}

void loop() {
    
        char c = gpsSerial.read();
        Serial.print(c);         // Print NMEA data to Serial Monitor
    
}