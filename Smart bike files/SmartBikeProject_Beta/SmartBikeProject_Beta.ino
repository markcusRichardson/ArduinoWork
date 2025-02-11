//Libraries
#include <Wire.h>
#include <FastLED.h>
#include "PinChangeInterrupt.h"



//Accelerometer
const int MPU_ADDR = 0x68;
int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;
char tmp_str[7];
char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
int accX = 0;
int accY = 0;
int accZ = 0;
int gX = 0;
int gY = 0;
int gZ = 0;




//Leds
int i, k, j = 0;
CRGB leds_1[30];
CRGB leds_2[15];
CRGB leds_3[15];
bool once = true;
bool once1 = true;
int brightness;
int LED_BRIGHTNESS;
CRGBPalette16 currentPalette;
TBlendType currentBlending;
int w = 200;
int r = 0;



//Rf
bool onOffState = false;
bool lockUnlockState = false;
int OnOffPin = 2;
int lockUnlockPin = 3;
int lightSensor = 4;
bool stateLightSensor = false;
int countLights = 1;




//Buzzer
int buzzerPin = 12;




void setup() {
  delay(1000);
  //Accelerometer
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                  // PWR_MGMT_1 register
  Wire.write(0);                     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);




  //Leds
  FastLED.addLeds<WS2812, 8, GRB>(leds_1, 30);
  FastLED.addLeds<WS2812, 10, GRB>(leds_2, 15);
  FastLED.addLeds<WS2812, 9, GRB>(leds_3, 15);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,2000);


//LigjtSensor
  pinMode(A6, INPUT);




  //RF
  pinMode(OnOffPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(OnOffPin), switchState, RISING);
  pinMode(lockUnlockPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(lockUnlockPin), switchState1, RISING);
  pinMode(lightSensor, INPUT);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(lightSensor), handleLightButtonPress, RISING);




  //Buzzer
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  //On/Off
  while (onOffState == false) {
    delay(500);
    Serial.print(10034);
    Serial.println();
    fill_solid(leds_1, 5, CRGB(200,200,200));
    fill_solid(leds_2, 5, CRGB(200,0,0));
    fill_solid(leds_3, 5, CRGB(200,0,0));
    FastLED.show();
  }


  


  //locked
  while (lockUnlockState == true) {
    fill_solid(leds_1, 30, CRGB(0,0,0));
    fill_solid(leds_2, 15, CRGB(0,0,0));
    fill_solid(leds_3, 15, CRGB(0,0,0));
    FastLED.show();
    if (once == true){
    lock();
    once = false;
    once1 = true;
    }
      
      

    accelerometerMonitor();

    if (accX > 1 || accY > 1 || accX < -1 || accY < -1) {
      digitalWrite(buzzerPin, HIGH);
      for(i=0;i<=20;i++){
        Alarm();
        delay(400);
      }
    }
    digitalWrite(buzzerPin, LOW);
  }




//Unlocked
while (lockUnlockState == false) {
Serial.print(123);
    Serial.println();

    if (once1 == true){
    unLock();
    //loading();
    once1 = false;
    once = true;
    }
      fill_solid(leds_2, 15, CRGB(200,0,0));
    fill_solid(leds_3, 15, CRGB(200,0,0));
      FastLED.show();
      delay(3000);


    while (countLights == 1) {

      fillWhite();
      delay(1000);
      
      

      escapeCountWhileLoops();
    }




    while (countLights == 2) {      
      
      for(int i = 0;i<30;i++){
    leds_1[i] = CRGB(200, w, w);
    k = i / 2;
    leds_2[k] = CRGB(200,r,r);
    leds_3[k] = CRGB(200,r,r);
    FastLED.show();
    delay(15);
    
  }

    fill_solid(leds_1, 30, CRGB(0,0,0));
    fill_solid(leds_2, 15, CRGB(0,0,0));
    fill_solid(leds_3, 15, CRGB(0,0,0));
    delay(30);
    FastLED.show();

    
    
    if(r == 0){
      r=200;
    }
    else{
      r = 0;
    }

    if(w == 200){
      w=0;
    }
    else{
      w = 200;
    }
      escapeCountWhileLoops();
      
      
    }
    
  




  while (countLights == 3) {
    fill_solid(leds_2, 15, CRGB(200,0,0));
    fill_solid(leds_3, 15, CRGB(200,0,0));
    currentPalette = ForestColors_p;
    static uint8_t index = 0;
    index = index + 1; /* motion speed */
    PaletteColors(index);
    FastLED.show();
    FastLED.delay(10);
    

    escapeCountWhileLoops();
  }




  while (countLights == 4) {
    currentPalette = LavaColors_p;
    static uint8_t index = 0;
    index = index + 1; /* motion speed */
    PaletteColors(index);
    FastLED.show();
    FastLED.delay(10);
    
    
    escapeCountWhileLoops();
  }
  



  while (countLights == 5) {
    currentPalette = RainbowColors_p;
    static uint8_t index = 0;
    index = index + 1; /* motion speed */
    PaletteColors(index);
    FastLED.show();
    FastLED.delay(10);
    

    escapeCountWhileLoops();
  }

  }
}


  // Methods

  //Interrups methods
void escapeCountWhileLoops() {
  if (onOffState == false) {
    countLights = 10;
    lockUnlockState == true;
  }
  if (lockUnlockState == true) {
    countLights = 10;
    onOffState == true;
  }
}


void switchState() {
  if (onOffState == false) {
    onOffState = true;
  } else {
    onOffState = false;
  }
}


void switchState1() {
  if (lockUnlockState == false) {
    lockUnlockState = true;

  } else {
    lockUnlockState = false;
  }
}


void handleLightButtonPress() {
  if (countLights >= 5) {
    countLights = 0;
  }
  countLights ++;
}




// Fastled methods
void lock(void) {
  k = 204;
  j = 100;

  for (i = 0; i <= 100; i++) {
    fill_solid(leds_1, 30, CRGB(k, j, 0));
    fill_solid(leds_2, 15, CRGB(k, j, 0));
    fill_solid(leds_3, 15, CRGB(k, j, 0));
    FastLED.show();
    k = k - 2;
    j = j - 1;
    delay(20);
  }
  fill_solid(leds_1, 30, CRGB(0, 0, 0));
  fill_solid(leds_2, 15, CRGB(0, 0, 0));
  fill_solid(leds_3, 15, CRGB(0, 0, 0));
  FastLED.show();
}

void Alarm(void){
  fill_solid(leds_1, 30, CRGB(200, 100, 100));
  fill_solid(leds_2, 15, CRGB(0, 255, 0));
  fill_solid(leds_3, 15, CRGB(0, 0, 255));
  FastLED.show();
  delay(400);
  fill_solid(leds_1, 30, CRGB(0, 0, 0));
  fill_solid(leds_2, 15, CRGB(0, 0, 255));
  fill_solid(leds_3, 15, CRGB(0, 255, 0));
  FastLED.show();
}


void unLock(void) {
  fill_solid(leds_1, 30, CRGB(204, 100, 0));
  fill_solid(leds_2, 15, CRGB(204, 100, 0));
  fill_solid(leds_3, 15, CRGB(204, 100, 0));
  FastLED.show();
  delay(200);
  fill_solid(leds_1, 30, CRGB(0, 0, 0));
  fill_solid(leds_2, 15, CRGB(0, 0, 0));
  fill_solid(leds_3, 15, CRGB(0, 0, 0));
  FastLED.show();
  delay(200);
  fill_solid(leds_1, 30, CRGB(204, 100, 0));
  fill_solid(leds_2, 15, CRGB(204, 100, 0));
  fill_solid(leds_3, 15, CRGB(204, 100, 0));
  FastLED.show();
  delay(200);
  fill_solid(leds_1, 30, CRGB(0, 0, 0));
  fill_solid(leds_2, 15, CRGB(0, 0, 0));
  fill_solid(leds_3, 15, CRGB(0, 0, 0));
  FastLED.show();
  delay(500);
}


void loading(void) {
  for (i = 0; i <= 10; i++) {
    leds_1[i] = CRGB(255, 0, 0);
    FastLED.show();
    delay(100);
  }


  for (i = 10; i <= 20; i++) {
    leds_1[i] = CRGB(204, 100, 0);
    FastLED.show();
    delay(100);
  }

  for (i = 20; i <= 30; i++) {
    leds_1[i] = CRGB(0, 255, 0);
    FastLED.show();
    delay(100);
  }
}


void fillWhite() {
  brightness = analogRead(A6);
  if (brightness <= 100) {
    LED_BRIGHTNESS = 200;
  }
  if (brightness > 100 && brightness <= 250) {
    LED_BRIGHTNESS = 100;
  }
  if (brightness > 250 && brightness <= 750) {
    LED_BRIGHTNESS = 50;
  }
  if (brightness > 750) {
    LED_BRIGHTNESS = 10;
  }

  fill_solid(leds_1, 30, CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS));
  FastLED.show();
}


void PaletteColors(uint8_t index) {
  uint8_t brightness = 70;

  for (int i = 0; i < 30; ++i) {
    leds_1[i] = ColorFromPalette(currentPalette, index, brightness, currentBlending);
    index += 10;
    
  }
  
}

void PartyMode() {
  for(int i = 0;i<30;i++){
    leds_1[i] = CRGB(200,200,200);
    leds_2[i/2] = CRGB(200,0,0);
    leds_3[i/2] = CRGB(200,0,0);
    FastLED.show();
    
  }
}


//Accelerometer methods
void accelerometerMonitor() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7 * 2, true);

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();


  convert_int16_to_str(accelerometer_x);
  convert_int16_to_str(accelerometer_y);
  accX = accelerometer_x / 10000;
  accY = accelerometer_y / 10000;
}
