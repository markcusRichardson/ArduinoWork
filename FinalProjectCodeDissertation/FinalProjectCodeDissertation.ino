#include <Wire.h>                // Wire.h is for the communication with the accelerometer
#include <FastLED.h>             // FastLED.h library is for the operation of the addressable LEDS
#include "PinChangeInterrupt.h"  // PinChangeInterrupt.h library is used for adding more interrupt pins as the Elegoo nano only has 2
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

//Accelerometer
  const int MPU_ADDR = 0x68;
  int16_t accelerometer_x, accelerometer_y, accelerometer_z;  // Value from accelerometer
  char tmp_str[7];
  char* convert_int16_to_str(int16_t i) {  // COnversion of int to strings
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
int accX = 0;                   // Final value from accelerometer after conversion
int accY = 0;                   // Final value from accelerometer after conversion
int accZ = 0;                   // Final value from accelerometer after conversion


//LEDS
int i, k, j = 0;                // Values used in loops in LEDS
CRGB leds_rear_left[10];        // LED strip facing the rear left side 10 leds
CRGB leds_rear_right[10];       // LED strip facing the rear right side 10 leds

CRGB leds_logo_left[30];        // LEDS inside the case for the logo left 30 leds
CRGB leds_logo_right[30];       // LEDS inside the case for the logo right 30 leds

CRGB leds_middle_left[30];      // LEDS in the middel facing down for under illunination left 30 leds
CRGB leds_middle_right[30];     // LEDS in the middel facing down for under illunination right 30 leds

CRGB leds_front_left[15];       // LEDS facing forward on the shock absorbers left 15 leds
CRGB leds_front_right[15];      // LEDS facing foward on the shcok absorber right 15 leds


// Serial comms variables and booleans
bool lock_Unlock_state = false; // Boolean for System power on and off 
int Mode = 1;
const byte START_BYTE = 0xAA;
const byte END_BYTE = 0xFF;
int16_t brightness;

// PINS allocation
int leds_rear_left_pin = 2;
int leds_rear_right_pin = 3;    // LED strip facing the rear right side 10 leds
int leds_logo_left_pin = 4;     // LEDS inside the case for the logo left 30 leds
int leds_logo_right_pin = 5;    // LEDS inside the case for the logo right 30 leds
int leds_middle_left_pin = 6;   // LEDS in the middel facing down for under illunination left 30 leds
int leds_middle_right_pin = 7;  // LEDS in the middel facing down for under illunination right 30 leds
int leds_front_left_pin = 8;    // LEDS facing forward on the shock absorbers left 15 leds
int leds_front_right_pin = 9;   // LEDS facing foward on the shcok absorber right 15 leds
int indicator_right = 10;       // Button input for indicators right
int indicator_left = 11;        // Button input for indicators left
int buzzerPin = 12;             // Buzzer pins output for security system
int lightSensor = A6;
int GPS_RX = A1
int GPS_TX = A2

// States 
bool indicator_left = false;
bool indicator_right = false;
bool Alarm_bool = false;

// Serial comms devices
SoftwareSerial gpsSerial(GPS_RX, GPS_TX); 

// GPS variables
int Longtitude = 0;
int Altitude = 0;
int Speed = 0;
int Satelites = 0;
int Date = 0;
int Time = 0;

// Light sensor
int OUTSIDE_BRIGHTNESS = 0;
int brightnessEnvironment =0;
int LED_BRIGHTNESS = 0;


//SETUP stage
void setup() {
// Serial comms









// Accelerometer  
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);  // Begins a transmission to the I2C slave 
  Wire.write(0x6B);                  // PWR_MGMT_1 register
  Wire.write(0);                     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);        // End the transmission

//Leds
  FastLED.addLeds<WS2812, leds_rear_left_pin, GRB>(leds_rear_left, 10); // Setup LEDS leds_rear _left
  FastLED.addLeds<WS2812, leds_rear_right_pin, GRB>(leds_rear_right, 10); // Setup LEDS leds_rear_right

  FastLED.addLeds<WS2812, leds_logo_left_pin, GRB>(leds_logo_left, 30); // Setup LEDS leds_lgog_left
  FastLED.addLeds<WS2812, leds_logo_right_pin, GRB>(leds_logo_right, 30); // Setup LEDS leds_logo_right

  FastLED.addLeds<WS2812, leds_middle_left_pin, GRB>(leds_middle_left, 30); // Setup LEDS leds_middle_left
  FastLED.addLeds<WS2812, leds_middle_right_pin, GRB>(leds_middle_right, 30); // Setup LEDS leds_middel_right

  FastLED.addLeds<WS2812, leds_front_left_pin, GRB>(leds_front_left, 15); // Setup LEDS leds_front_left
  FastLED.addLeds<WS2812, leds_front_right_pin, GRB>(leds_front_right, 15); // Setup LEDS leds_front_right

  FastLED.setMaxPowerInVoltsAndMilliamps(5,3000); 

  //Buzzer
  pinMode(buzzerPin, OUTPUT); // Ouput pin for the buzzer for alarm
 

//LightSensor
  pinMode(lightSensor, INPUT);  // Input pin of the light sensor to detetc light

// Indicators
  pinMode(indicator_right, INPUT_PULLUP);
  pinMode(indicator_left, INPUT_PULLUP);


}

void loop() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
    Serial_Decode()



    
//locked: This is the locked state of the system
  while (lock_Unlock_state  == true) {    

    accelerometerMonitor();  // Method for gathering the g forces meaudred on x and y axis

    if (accX > 1 || accY > 1 || accX < -1 || accY < -1 || accZ < -1 || accZ < -1) {
      Alarm_bool = true;
      while (Alarm_bool == true)
      digitalWrite(buzzerPin, HIGH);
      gpsDecodeData();
      for(i=0;i<=50;i++){
        Alarm();
        delay(5);
      }
      Serial_decode();

    }
    digitalWrite(buzzerPin, LOW);


  }


//Unlocked: This is the unlocked state of the system
while (lock_Unlock_state == false) {
    


  while(Mode == 1){ // Automatic mode

    if(indicator_left == true;)
    LED_BRIGHTNESS = 255 * OUTSIDE_BRIGHTNESS;
    fill_solid(leds_rear_left_pin, 10, CRGB(LED_BRIGHTNESS, 0, 0));
    fill_solid(leds_logo_left_pin, 21, CRGB(0, 200, 0));
    fill_solid(leds_middle_left_pin, 21, CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS));
    fill_solid(leds_front_left_pin, 15, CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS));
    else if(indicator_left = false;){
      for (int i = 0; i < 21; i++) {
      leds_middle_left_pin[i] = CHSV(43, 255, 255);
      leds_rear_left_pin[i] = CHSV(43, 255, 255);
      leds_logo_left_pin[i] = CHSV(43, 255, 255);
      leds_middle_left_pin[i] = CHSV(43, 255, 255);
      FastLED.show();
      delay(10); // Speed of filling
    }
    }

    if (indicator_right == true;)
    fill_solid(leds_middle_right_pin, 15, CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS));
    fill_solid(leds_rear_right_pin, 10, CRGB(LED_BRIGHTNESS, 0, 0));
    fill_solid(leds_logo_right_pin, 21, CRGB(0, 200, 0));
    fill_solid(leds_middle_right_pin, 21, CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS));
    else if(indicator_right = false){
    for (int i = 0; i < 21; i++) {
      leds_middle_right_pin[i] = CHSV(43, 255, 255);
      leds_rear_right_pin[i] = CHSV(43, 255, 255);
      leds_logo_right_pin[i] = CHSV(43, 255, 255);
      leds_middle_right_pin[i] = CHSV(43, 255, 255);
      FastLED.show();
      delay(10); // Speed of filling
    }
    }

    indicator_state()
    gpsDecodeData()
    Serial_Encode()
    Serial_Decode()
  }

   while(Mode == 2){ // Daytime time mode



    indicator_state()
    gpsDecodeData()
    Serial_Encode()
    Serial_Decode()
  }

   while(Mode == 3){ // Nigh time mode
   


    indicator_state()
    gpsDecodeData()
    Serial_Encode()
    Serial_Decode()
  }

   while(Mode == 4){ // Custom mode



    indicator_state()
    gpsDecodeData()
    Serial_Encode()
    Serial_Decode()
  }

}



void gpsDecodeData(){
gps.encode(gpsSerial.read());
if (gps.location.isUpdated()) {  // If a new location update is available
    Longtitude = gps.location.lng(), 6;
    Latitude = gps.location.lat() 6;
    Altitude = gps.altitude.meters();
    Speed = gps.speed.kmph();
    Satellites = gps.satellites.value();
    Date = gps.date.day();
    Time = gps.time.hour();
    TimeM = gps.time.minute();
}

void Serial_Encode(){
    Serial.write(START_BYTE);  // Start Byte

    Serial.write((byte*)&longitude, sizeof(longitude)); 
    Serial.write((byte*)&latitude, sizeof(latitude));   
    Serial.write((byte*)&altitude, sizeof(altitude));   
    Serial.write((byte*)&speed, sizeof(speed));         
    Serial.write((byte*)&satellites, sizeof(satellites));  
    Serial.write((byte*)&date, sizeof(date));           
    Serial.write((byte*)&hour, sizeof(hour));           
    Serial.write((byte*)&minute, sizeof(minute));
    Serial.write(Alarm_bool);

    Serial.write(END_BYTE);  // End Byte
}
}

void Serial_Decode(){
  if (Serial.available() >= 9) {  // Wait for at least 9 bytes (Start + 7 Data + End)
        if (Serial.read() == START_BYTE) {  // Check for the Start Byte
            Serial.readBytes((char *)&var1, 7);  // Read the next 7 bytes into variables
            byte endMarker = Serial.read();  // Read End Byte
            if (endMarker == END_BYTE) {  // Validate the End Byte

                // Print received values
                Lock_Unlock (val1);
                Mode (val2); // Number from 1-4
                Alarm_bool_state (val3);

            } else {
                Serial.println("Error: End Byte Mismatch!");
            }
        } else {
            Serial.println("Error: Start Byte Mismatch!");
        }
    }

}

void indicator_state(){
  if (digitalRead(indicator_right) == LOW) {  //Button activated right
    indicator_left = true;


  }
  else if(digitalRead(indicator_right) == HIGH){
    indicator_left = false;

  }

  if (digitalRead(indicator_left) == LOW) {  // Button activated left
    indicator_right = false;

  }

  else if(digitalRead(indicator_left) == HIGH){
    indicator_right = false;

  }
}

void Mode(value){
if (value == 1){
  Mode = 1;

} else if(value == 2){
  Mode = 2;

} else if(value == 3)
  Mode=3;

} else if(value == 4){
  mode = 4;
} 

void Alarm_bool_state(value){
  if (value == true){
    Alarm_bool = true;
  }

  if else(value == false){
    Alarm_bool = false;
  }
}

void Lock_Unlock(value){ // Switch state for on/off boolean switch
  if(value == false) {
    Lock_Unlock_state = false;
  } else {
    Lock_Unlock_state = true;
  }

}



void unlock() { // Effect done upon locking the smart bike
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // Clear the strip

    brightnessPulse = beatsin8(20, 100, 255);  // Smooth pulsing effect

    for (int i = 0; i < 30; i++) {  // Trail length
        int index = (pos - i + NUM_LEDS) % NUM_LEDS;  // Wrap around
        leds[index] = CHSV(50, 255, brightnessPulse - (i * 40));  // Yellow pulsing streak
    }

    // Leave a filled trail behind
    for (int j = 0; j < pos; j++) {
        leds[j] = CHSV(50, 255, 150);  // Solid yellow fill
    }

    FastLED.show();
    pos++;

    // Once full strip is filled, reverse direction
    if (pos >= NUM_LEDS) {
        streakForward = false;
        pos = NUM_LEDS - 1;  // Start at end for streak back
    }

    delay(30);



void streakBackToDRL_Unlocked() {
    fill_solid(leds, NUM_LEDS, CRGB(50, 50, 10));  // DRL base glow

    brightnessPulse = beatsin8(20, 100, 255);  // Pulsing brightness for returning streak

    for (int i = 0; i < 5; i++) {  // Trail length
        int index = (pos + i) % NUM_LEDS;  // Wrap around
        leds[index] = CHSV(50, 255, brightnessPulse - (i * 40));  // Yellow pulsing streak
    }

    FastLED.show();
    pos--;

    // Once back at the start, DRL stays on
    if (pos <= 0) {
        streakForward = true;  // Reset for next cycle
    }

    delay(30);
}
}

void streakBackToDRL_Locked() {
    fill_solid(leds, NUM_LEDS, CRGB(50, 50, 10));  // DRL base glow

    brightnessPulse = beatsin8(20, 100, 255);  // Pulsing brightness for returning streak

    for (int i = 0; i < 5; i++) {  // Trail length
        int index = (pos + i) % NUM_LEDS;  // Wrap around
        leds[index] = CHSV(50, 255, brightnessPulse - (i * 40));  // Yellow pulsing streak
    }

    FastLED.show();
    pos--;

    // Once back at the start, DRL stays on
    if (pos <= 0) {
        streakForward = true;  // Reset for next cycle
    }

    delay(30);
}
}

//Accelerometer method
void accelerometerMonitor() { // Method for monitoring acceleromater readings
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7 * 2, true);

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();

  convert_int16_to_str(accelerometer_x);
  convert_int16_to_str(accelerometer_y);
  convert_int16_to_str(accelerometer_z);
  accX = accelerometer_x / 10000;
  accY = accelerometer_y / 10000;
  accZ = accelerometer_z / 10000;
}


void Alarm(void){
  int intensity = 0;
  static int direction = 5; // Change intensity in steps

  intensity += direction;
  if (intensity <= 0 || intensity >= 255) direction = -direction; // Reverse

  fill_solid(leds_middle_left_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();
  fill_solid(leds_rear_right_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();

  fill_solid(leds_logo_left_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();
  fill_solid(leds_logo_right_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();

  fill_solid(leds_logo_left_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();
  fill_solid(leds_logo_right_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();

  fill_solid(leds_logo_left_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();
  fill_solid(leds_logo_right_pin, 30, CHSV(43, 255, intensity)); // Red flashing
  FastLED.show();

  
}


void lightSensor() { 
  brightnessEnvironment = analogRead(A6);  // Read sensor (0-1023)
  OUTSIDE_BRIGHTNESS = 1.24 * (1 - (brightnessEnvironment / 1023.0));  // Reverse value
}

