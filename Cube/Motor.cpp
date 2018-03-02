#include <Arduino.h>
#include <Servo.h>

class Motor {
  Servo servo;
  int servoPin;
  int pullPos = 52;
  int pushPos = 130;

  bool pushed = false;
  bool wigwaging = false;
  bool rapidWigwaging = false;
  
  unsigned long longInterval = 60000;
  const int shortInterval = 1000;
  unsigned long previousMillis = 0;
  
  public:
  Motor(int newServoPin) {
    servoPin = newServoPin;
    servo.attach(servoPin);
    instPull();
  }

  void Update() {
    if (rapidWigwaging){
      rapidWigwag();
    } else if(wigwaging){
      wigwag();
    }
  }

  void instPush(){
    servo.write(pushPos);
    pushed = true;
  }

  void instPull(){
    servo.write(pullPos);
    digitalWrite(servoPin, LOW);
    pushed = false;
  }

  void instOpposite(){
    if (pushed){
      instPull();
    } else {
      instPush();  
    }
  }

  void startWigwag(){
    wigwaging = true;
    previousMillis = millis() - longInterval;
  }

  void startRapidWigwag(){
    rapidWigwaging = true;  
  }

  void stopWigwag(){
    wigwaging = false;
    instPull();
  }
  
  void stopRapidWigwag(){
    rapidWigwaging = false;
    instPull();  
  }

  void wigwag(){
    unsigned long currentMillis = millis();

    unsigned long interval = (pushed) ? shortInterval : longInterval;
    if (currentMillis - previousMillis >= interval) {
  
      previousMillis = currentMillis;
      instOpposite();
    }
  }
  
  void rapidWigwag(){
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= shortInterval) {
      previousMillis = currentMillis;
      instOpposite();
    }
  }
};
