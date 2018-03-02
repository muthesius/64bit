#include <Arduino.h>

class RGBLight {
  int redPin;
  int greenPin;
  int bluePin;
  
  int redColor = 255;
  int greenColor = 255;
  int blueColor = 255;
  
  bool currentState = false;
  bool isBlinking = false;
  
  const int interval = 1000;
  unsigned long previousMillis = 0;
  
  public:
  RGBLight(int red, int green, int blue) {
    redPin = red;
    greenPin = green;
    bluePin = blue;
    
    pinMode(redPin, OUTPUT); 
    pinMode(greenPin, OUTPUT); 
    pinMode(bluePin, OUTPUT);     
  }

  void Update() {
    if(isBlinking){
      blink();  
    }
  }
  
  void turn(bool state){
    int newState = (int)state;
    int newRed = redColor * newState;
    int newGreen = greenColor * newState;
    int newBlue = blueColor * newState;
    
    analogWrite(redPin, newRed);
    analogWrite(greenPin, newGreen);
    analogWrite(bluePin, newBlue); 
    currentState = state;
  } 

  void on(){
    turn(true);
  }

  void off(){
    turn(false);
  }

  void flip(){
    turn(!currentState);
  }

  void setColor(int newRed, int newGreen, int newBlue){
    redColor = newRed;
    greenColor = newGreen;
    blueColor = newBlue;

    turn(currentState);
  }

  void startBlinking(){
    isBlinking = true;
  }

  void stopBlinking(){
    isBlinking = false;
  }

  void blink(){
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
  
      previousMillis = currentMillis;
      flip();
    }
  }
};
