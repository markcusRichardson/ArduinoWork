#include <SoftwareSerial.h>
#include <radar.h>
#include <Adafruit_AMG88xx.h>
#include <Wire.h>
#include "PinChangeInterrupt.h" 

// IR sensor 
  int MotionInterrupt = 9;
  int NUM_SEGMENTS = 4;
  int segments[4] = {0};
  Adafruit_AMG88xx amg;
  // Paramaters for IR sensor
  int Threshold_TEMP = 25;
  int Movement_Threshold = 3;
  // Variables
  float pixels[64];
  float previousPixels[64];
  float ambientTEMP =0;

// Radar
bool detectionRadar = true;


void setup() {

Serial.begin(9600);
amg.begin();
// Interrups



amg.setMovingAverageMode(false);



}

void loop() {

amg.readPixels(pixels);
ambientTEMP = amg.readThermistor();
Serial.print("Temp"); 
Serial.println(ambientTEMP);
 


delay(500);

    analyzeHeatmap(pixels);

    // Output segment data
    for (int i = 0; i < NUM_SEGMENTS; i++) {
      Serial.print("Segment ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(segments[i]);
    }



}

void analyzeHeatmap(float pixels[]) {
  // Reset segment heat intensities
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    segments[i] = 0;
  }

  // Divide heatmap into 4 horizontal segments
  for (int col = 0; col < 8; col++) {       // Iterate through columns
    for (int row = 0; row < 8; row++) {     // Iterate through rows
      int segmentIndex = row / 2;           // Each segment spans 2 rows
      if (pixels[row * 8 + col] > ambientTEMP + 2) {
        segments[segmentIndex]++;
      }
    }
  }
}