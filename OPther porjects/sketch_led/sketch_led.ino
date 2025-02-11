#include <FastLED.h>
int once = 1;
int oncee = 1;
int once2 = 1;
int i = 0;
int k = 0;
CRGB leds[60];


void setup() {

  FastLED.addLeds<WS2812, 8, GRB>(leds, 60);
  
}
void flashYellowOpen(void){
    fill_solid( leds, 60, CRGB(204,100,0));
    FastLED.show();
    delay(200);
    fill_solid( leds, 60, CRGB(0,0,0));
    FastLED.show();
    delay(200);
    fill_solid( leds, 60, CRGB(204,100,0));
    FastLED.show();
    delay(200);
    fill_solid( leds, 60, CRGB(0,0,0));
    FastLED.show();
    delay(500);
  }

  void trafficLight(void){
for (i=0;i<=21;i++){
  leds[i] = CRGB(255, 0, 0);
  FastLED.show();
  delay(100);
  
}


for (i=21;i<=42;i++){
  leds[i] = CRGB(204, 100, 0);
  FastLED.show();
  delay(100);
  
}

for (i=42;i<=60;i++){
  leds[i] = CRGB(0, 255, 0);
  FastLED.show();
  delay(100);
  
}

  }

void loop() {

flashYellowOpen();
trafficLight();
fill_solid( leds, 60, CRGB(0,0,0));
FastLED.show();

for(k=0;k<=160;k++){
  fill_solid( leds, 60, CRGB(k,0,k));
  FastLED.show();
  delay(500);
  fill_solid( leds, 60, CRGB(0,k,0));
  FastLED.show();
}

for(k=0;k<=60;k++){
  leds[i] = CRGB(25, 35, 150);
  FastLED.show();
  delay(200);
}
delay(2000);





}
  
  
    


  
   

