#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

// Parameters
#define TEMP_THRESHOLD 27.0 
#define MOVEMENT_THRESHOLD 3.0 

// Variables
float pixels[64];        
float prevPixels[64];    
bool radarTriggered = true;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize the AMG8833 sensor
  if (!amg.begin()) {
    Serial.println("AMG88xx sensor not found. Check wiring!");
    while (1);
  }
  Serial.println("AMG88xx initialized");

  // Set up radar input pin
  pinMode(RADAR_PIN, INPUT);
}

void loop() {
  // Check radar signal
  radarTriggered = true;

  if (radarTriggered) {
    Serial.println("Radar detected movement!");

    // Read IR data from AMG8833
    amg.readPixels(pixels);

    // Analyze the data
    if (detectInfraredObject(pixels)) {
      if (checkMovement(pixels, prevPixels)) {
        Serial.println("Moving heat-emitting object detected!");
      } else {
        Serial.println("Stationary heat source detected.");
      }
    } else {
      Serial.println("No significant heat source detected.");
    }

    // Store the current readings as the previous frame
    memcpy(prevPixels, pixels, sizeof(pixels));
  }

  delay(500); // Adjust delay for responsiveness
}

// Function to detect a heat-emitting object
bool detectInfraredObject(float *data) {
  for (int i = 0; i < 64; i++) {
    if (data[i] > TEMP_THRESHOLD) {
      return true; // Object detected
    }
  }
  return false; // No heat source detected
}

// Function to check movement by comparing frames
bool checkMovement(float *current, float *previous) {
  float movementSum = 0;

  for (int i = 0; i < 64; i++) {
    movementSum += abs(current[i] - previous[i]);
  }

  // If the total change in temperature exceeds the threshold, confirm movement
  return movementSum > MOVEMENT_THRESHOLD;
}