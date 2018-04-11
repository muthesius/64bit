# Connected Cubes

64-bit Winter term 2017/2018 

## Description

The Projects main idea is to displays a basic network and communication structure via tree rotating cubes,
on a distance between India and Germany. The cubes are spread across 3 different campuses and locations: one is placed at the National Institute of Design (NID) Campus in Ahmedabad, one at the NID Campus in Gandhinagar in India and one at the Muthesius Kunsthochschule Kiel Germany.

### How it works

When the cube is turned from one side to another, it sends a signal to the other cubes. If the cube receives a signal, it starts to tilt itself every 60 seconds.
The current implementation of the cubes only support four sides of the cube - the one with the faces on it. If the cube is placed on one of the other two sides, the motor will push and pull continuously.

To turn the cubes on or off there is a switch right next to the LED (LED-side => on, USB-side => off). The current version of the cubes are powered by a 750mAh LiPo-Battery. They can be chard via the visible micro USB port.
This USB port only supports power, whereas the internal micro USB port supports a data connection. It is accessible by removing the side with the IO ports on it.

### LED Colors

* Yellow: Setup connection to WIFI network
* Blue: Setup connection to MQTT server
* Green: Setup MPU6050 sensor
* White: Calibration process of accelerometer and gyroscopes (takes 12s)

## Diary Documentation German Cube

http://piratepad.net/64bit-Cube-Germany

## Todo

- [ ] Check how long a cube lasts on a full charge.
- [ ] LED should indicate if there is still power and how much.
