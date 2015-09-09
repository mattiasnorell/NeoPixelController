#include <Adafruit_NeoPixel.h>

int redPin = A0;
int greenPin = A1;
int bluePin = A2;
int brightnessPin = A3;
int startPixelPin = A4;
int sectionBrightnessPin = A5;
int rotationPin = A6;

int FULL_ON = 3;
int FULL_OFF = 4;
int pixelPin = 2;
int PIN_COUNT = 16;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIN_COUNT, pixelPin, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(FULL_ON, INPUT);
  digitalWrite(FULL_ON, HIGH);

  pinMode(FULL_OFF, INPUT);
  digitalWrite(FULL_OFF, HIGH);
  
  pixels.begin();
}

void loop() {

  SetBrightness();
  SetColors();
  
  pixels.show();
 
  delay(100);
}

void SetBrightness(){
  if(!digitalRead(FULL_ON)){
    pixels.setBrightness(100);
  }else if(!digitalRead(FULL_OFF)){
    pixels.setBrightness(0);
  }else{
    pixels.setBrightness(ReadValueFromPin(brightnessPin, 100));
  }
}

void SetColors(){
  int start = ReadValueFromPin(startPixelPin, PIN_COUNT-1);
  int brightness = ReadValueFromPin(sectionBrightnessPin, 255);
  int rotation = GetRotation();
  
  for (int i = 0; i < PIN_COUNT; i++) {
    int pixelId = i + rotation;

    if(i + rotation > (PIN_COUNT - 1)){
      pixelId = (i + rotation) - (PIN_COUNT);
    }
    
    if(start > i && digitalRead(FULL_ON)){
      pixels.setPixelColor(pixelId, pixels.Color((brightness*ReadValueFromPin(redPin, 255)/255), (brightness*ReadValueFromPin(greenPin, 255)/255), (brightness*ReadValueFromPin(bluePin, 255)/255)));      
    }else{
      pixels.setPixelColor(pixelId, pixels.Color(ReadValueFromPin(redPin, 255), ReadValueFromPin(greenPin, 255), ReadValueFromPin(bluePin, 255)));    
    }
  }  
}

int GetRotation(){
  return ReadValueFromPin(rotationPin, PIN_COUNT-1);
}

int ReadValueFromPin(int pinId, int maxValue) {
  int value = analogRead(pinId);
  return map(value, 0 , 1023, 0, maxValue);
}
