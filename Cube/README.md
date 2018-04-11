<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <meta http-equiv="Content-Style-Type" content="text/css">
  <title></title>
  <meta name="Generator" content="Cocoa HTML Writer">
  <meta name="CocoaVersion" content="1504.83">
  <style type="text/css">
    p.p1 {margin: 0.0px 0.0px 0.0px 0.0px; font: 12.0px Helvetica}
    p.p2 {margin: 0.0px 0.0px 0.0px 0.0px; font: 12.0px Helvetica; min-height: 14.0px}
    p.p3 {margin: 0.0px 0.0px 0.0px 0.0px; font: 13.0px Arial; color: #333333; -webkit-text-stroke: #000000}
    p.p4 {margin: 0.0px 0.0px 0.0px 0.0px; font: 13.0px Arial; color: #333333; -webkit-text-stroke: #000000; background-color: #ffffff; min-height: 15.0px}
    p.p5 {margin: 0.0px 0.0px 0.0px 0.0px; font: 13.0px Arial; color: #333333; -webkit-text-stroke: #000000; background-color: #ffffff}
    span.s1 {font: 12.0px Helvetica; color: #000000; -webkit-text-stroke: 0px #000000}
    span.s2 {font-kerning: none; background-color: #ffffff}
    span.s3 {font-kerning: none}
  </style>
</head>
<body>
<p class="p1"># Connected Cubes</p>
<p class="p2"><br></p>
<p class="p1">64-bit Winter term 2017/2018<span class="Apple-converted-space"> </span></p>
<p class="p2"><br></p>
<p class="p1">## Description</p>
<p class="p2"><br></p>
<p class="p1">The Projects main idea is to displays a basic network and communication structure via tree rotating cubes,</p>
<p class="p3"><span class="s1">on a distance between India and Germany. The cubes are spread across 3 different campuses and locations: one is placed at the </span><span class="s2">National Institute of Design (NID) Campus in Ahmedabad, one at the NID Campus in Gandhinagar in India and one at the Muthesius Kunsthochschule Kiel Germany.</span></p>
<p class="p4"><span class="s3"></span><br></p>
<p class="p5"><span class="s3">### How it works</span></p>
<p class="p4"><span class="s3"></span><br></p>
<p class="p5"><span class="s3">When the cube is turned from one side to another, it sends a signal to the other cubes. If the cube receives a signal, it starts to tilt itself every 60 seconds.</span></p>
<p class="p5"><span class="s3">The current implementation of the cubes only support four sides of the cube - the one with the faces on it. If the cube is placed on one of the other two sides, the motor will push and pull continuously.</span></p>
<p class="p4"><span class="s3"></span><br></p>
<p class="p5"><span class="s3">To turn the cubes on or off there is a switch right next to the LED (LED-side =&gt; on, USB-side =&gt; off). The current version of the cubes are powered by a 750mAh LiPo-Battery. They can be chard via the visible micro USB port.</span></p>
<p class="p5"><span class="s3">This USB port only supports power, whereas the internal micro USB port supports a data connection. It is accessible by removing the side with the IO ports on it.</span></p>
<p class="p2"><br></p>
<p class="p1">### LED Colors</p>
<p class="p2"><br></p>
<p class="p1">* Yellow: Setup connection to WIFI network</p>
<p class="p1">* Blue: Setup connection to MQTT server</p>
<p class="p1">* Green: Setup MPU6050 sensor</p>
<p class="p1">* White: Calibration process of accelerometer and gyroscopes (takes 12s)</p>
<p class="p2"><br></p>
<p class="p1">## Diary Documentation German Cube</p>
<p class="p2"><br></p>
<p class="p1">http://piratepad.net/64bit-Cube-Germany</p>
<p class="p2"><br></p>
<p class="p1">## Todo</p>
<p class="p2"><br></p>
<p class="p1">-[ ] Check how long a cube lasts on a full charge.</p>
<p class="p1">-[ ] LED should indicate if there is still power and how much.</p>
<p class="p2"><br></p>
</body>
</html>
