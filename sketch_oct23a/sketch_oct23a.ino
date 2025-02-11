#include <LiquidCrystal.h>
int tempPin = A0;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  // put your setup code here, to run once:
lcd.begin(16, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
int tempReading = analogRead(tempPin);
double tempK = log(10000 * ((1024.0 / tempReading - 1)));
tempK = 1 / (0.001129148 + (0.000234125 +(0.0000000876741 * tempK *tempK)) *tempK);
float tempC = tempK - 273.15;
float tempF = (tempC * 9.0) / (5.0 + 32.0);

lcd.setCursor(0,0);
lcd.print("Temp         F  ");
lcd.setCursor(6,0);
lcd.print(tempF);
delay(50);
}
