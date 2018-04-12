int ID = 3; //You can find the ID of the cube on the inside of the cap

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "I2Cdev.h"
#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "Light.cpp"
#include "Motor.cpp"

WiFiClient espClient;
PubSubClient client(espClient);
RGBLight led = RGBLight(D5, D6, D7);
Motor motor = Motor(2);

MPU6050 mpu;

int previousSide = 1;
int newState = false;
int newSide = 0;

void setup() {
  Serial.begin(9600);
  
  led.setColor(255, 100, 0);
  led.on();
  setup_wifi();
  
  led.setColor(0,0,255);
  setup_mqtt();

  led.setColor(0,255,0);
  setup_mpu();

  led.setColor(255,255,255);
  delay(12000);

  previousSide = getSide();
  
  led.off();
}

void loop() {
  mqtt_Update();
  
  
  led.Update();
  motor.Update();
  mpu_Update();
  
  newSide = getSide();
  Serial.println(newSide);

  if(newSide == 0){
    motor.startRapidWigwag();
    
  } else if (newSide != 0){
    
    if(previousSide == 0){
      motor.stopRapidWigwag();
    }
    if (validRotation() && !newState && previousSide != 0){
      Serial.println("Send comand");
      sendStatus(newSide);
      motor.stopWigwag();
    } else if (newState && validRotation()){
      Serial.println("Done");
      motor.stopWigwag();
      newState = false;
    } 
  }
  previousSide = newSide;
  delay(100);
}

bool validRotation(){
  return (previousSide != newSide);
}
