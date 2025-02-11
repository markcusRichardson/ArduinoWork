int BrightnessRed = 255;
int BrightnessBlue = 0;
int BrightnessGreen = 125;
int FadeAmountG = -5;
int FadeAmountR = -5;
int FadeAmountB = 5;


void setup() {
  // put your setup code here, to run once:

pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);




}
void loop() {
  analogWrite(9, BrightnessBlue );
  analogWrite(10, BrightnessRed );
  analogWrite(11, BrightnessGreen );
  



BrightnessBlue = BrightnessBlue + FadeAmountB;
BrightnessRed = BrightnessRed + FadeAmountR;
BrightnessGreen = BrightnessGreen + FadeAmountG;

if(BrightnessBlue >= 255 || BrightnessBlue<=0){
  FadeAmountB=-FadeAmountB;
}
if(BrightnessRed >= 255 || BrightnessRed<=0){
  FadeAmountR=-FadeAmountR;
}
if(BrightnessGreen >= 255 || BrightnessGreen<=0){
  FadeAmountG=-FadeAmountG;
}
delay(3);







}
