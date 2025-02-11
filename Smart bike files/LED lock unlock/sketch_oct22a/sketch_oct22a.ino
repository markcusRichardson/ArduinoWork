#include <FastLED.h>
int once = 1;
int oncee = 1;
int once2 = 1;
int i = 0;
int k = 0;
int j = 0;
CRGB leds_1[30];
CRGB leds_2[15];
CRGB leds_3[15];



void setup() {

  FastLED.addLeds<WS2812, 11, GRB>(leds_1, 30);
  FastLED.addLeds<WS2812, 10, GRB>(leds_2, 15);
  FastLED.addLeds<WS2812, 9, GRB>(leds_3, 15);
  
}
void unlock(void){
    fill_solid( leds_1, 30, CRGB(204,100,0));
    fill_solid( leds_2, 15, CRGB(204,100,0));
    fill_solid( leds_3, 15, CRGB(204,100,0));
    FastLED.show();
    delay(200);
    fill_solid( leds_1, 30, CRGB(0,0,0));
    fill_solid( leds_2, 15, CRGB(0,0,0));
    fill_solid( leds_3, 15, CRGB(0,0,0));
    FastLED.show();
    delay(200);
   fill_solid( leds_1, 30, CRGB(204,100,0));
    fill_solid( leds_2, 15, CRGB(204,100,0));
    fill_solid( leds_3, 15, CRGB(204,100,0));
    FastLED.show();
    delay(200);
    fill_solid( leds_1, 30,  CRGB(0,0,0));
    fill_solid( leds_2, 15, CRGB(0,0,0));
    fill_solid( leds_3, 15, CRGB(0,0,0));
    FastLED.show();
    delay(500);
  }

  void lock(void){
    k = 204;
    j = 100;
    
    for (i=0;i<=100;i++){
      fill_solid( leds_1, 30, CRGB(k,j,0));
      fill_solid( leds_2, 15, CRGB(k,j,0));
      fill_solid( leds_3, 15, CRGB(k,j,0));
      FastLED.show();
      k = k - 2;
      j = j - 1;
      delay(20);
    }
      fill_solid( leds_1, 30, CRGB(0,0,0));
      fill_solid( leds_2, 15, CRGB(0,0,0));
      fill_solid( leds_3, 15, CRGB(0,0,0));
  }

  void loading(void){
for (i=0;i<=21;i++){
  leds_1[i] = CRGB(255, 0, 0);
  leds_2[i] = CRGB(255, 0, 0);
  leds_3[i] = CRGB(255, 0, 0);
  FastLED.show();
  delay(100);
  
}


for (i=21;i<=42;i++){
  leds_1[i] = CRGB(204, 100, 0);
  leds_2[i] = CRGB(204, 100, 0);
  leds_3[i] = CRGB(204, 100, 0);
  FastLED.show();
  delay(100);
  
}

for (i=42;i<=60;i++){
  leds_1[i] = CRGB(0, 255, 0);
  leds_2[i] = CRGB(0, 255, 0);
  leds_3[i] = CRGB(0, 255, 0);
  FastLED.show();
  delay(100);
  
}

  }

void loop() {

unlock();
lock();
loading();



}