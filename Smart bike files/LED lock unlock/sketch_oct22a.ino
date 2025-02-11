#include <FastLED.h>
int once = 1;
int oncee = 1;
int once2 = 1;
int i = 0;
int k = 0;
int j = 0;
CRGB leds[60];


void setup() {

  FastLED.addLeds<WS2812, 8, GRB>(leds, 60);
  
}
void unlock(void){
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

  void lock(void){
    k = 204;
    j = 100;
    
    for (i=0;i<=100;i++){
      fill_solid( leds, 60, CRGB(k,j,0));
      FastLED.show();
      k = k - 2;
      j = j - 1;
      delay(20);
    }
    fill_solid( leds, 60, CRGB(0,0,0));
  }

  void loading(void){
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

unlock();
lock();
loading();



}