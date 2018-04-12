bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

//Offset is defined for ID (1,2 and 3)
int offset[3][6] = {
  {-852, 13, 1162, 127, 42, 10},
  {-3525, -1367, 1722, 209, 0, -20},
  {-2436, 1956, 1767, 122, -39, -39}
};

int angleThreshold = 45;

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];
float euler[3];
  
int INTERRUPT_PIN = 15;
volatile bool mpuInterrupt = false;

void mpu_Update() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    if (!mpuInterrupt && fifoCount < packetSize) return;

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
      // reset so we can continue cleanly
      mpu.resetFIFO();
      //Serial.println("FIFO overflow!");

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
      // wait for correct available data length, should be a VERY short wait
      while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

      // read a packet from FIFO
      mpu.getFIFOBytes(fifoBuffer, packetSize);

      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount -= packetSize;
/*
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      Serial.print("quat\t");
      Serial.print(q.w);
      Serial.print("\t");
      Serial.print(q.x);
      Serial.print("\t");
      Serial.print(q.y);
      Serial.print("\t");
      Serial.println(q.z);

      */
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      /*
      Serial.print("ypr\t");
      Serial.print(ypr[0] * 180/M_PI);
      Serial.print("\t");
      Serial.print(ypr[1] * 180/M_PI);
      Serial.print("\t");
      Serial.println(ypr[2] * 180/M_PI);
      */
/*
      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetEuler(euler, &q);
      Serial.print("euler\t");
      Serial.print(euler[0] * 180/M_PI);
      Serial.print("\t");
      Serial.print(euler[1] * 180/M_PI);
      Serial.print("\t");
      Serial.println(euler[2] * 180/M_PI);*/
    }
  }
  

  void setup_mpu()
  {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties

    // initialize device
    Serial.println("Initializing I2C devices...");
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // load and configure the DMP
    Serial.println("Initializing DMP...");
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    int arrayLength = sizeof (offset) / sizeof (offset[0]);
    if(arrayLength >= ID){
      int offsetIndex = ID-1;
      mpu.setXAccelOffset(offset[offsetIndex][0]);
      mpu.setYAccelOffset(offset[offsetIndex][1]);
      mpu.setZAccelOffset(offset[offsetIndex][2]);
      mpu.setXGyroOffset(offset[offsetIndex][3]);
      mpu.setYGyroOffset(offset[offsetIndex][4]);
      mpu.setZGyroOffset(offset[offsetIndex][5]);
    }

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
      // turn on the DMP, now that it's ready
      Serial.println("Enabling DMP...");
      mpu.setDMPEnabled(true);

      // enable Arduino interrupt detection
      Serial.println("Enabling interrupt detection (Arduino external interrupt 0)...");
      attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();

      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      Serial.println("DMP ready! Waiting for first interrupt...");
      dmpReady = true;

      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print("DMP Initialization failed (code ");
      Serial.print(devStatus);
      Serial.println(")");
    }
  }
  void dmpDataReady() {
    mpuInterrupt = true;
  }

  bool isMoving(){
    return false;
  }

  int getSide(){
    long yaw = ypr[0] * 180/M_PI;
    long pitch = ypr[1] * 180/M_PI;
    long roll = ypr[2] * 180/M_PI;
    //Serial.print(yaw);
    //Serial.print(": ");
    if (pitch >= (0-25) && pitch <= (0+25) &&
        roll >= (0-25) && roll <= (0+25)){
      return 0;
    } else if((90+angleThreshold) >= yaw && yaw >= (90-angleThreshold)){
      return 1;
    } else if(yaw >= (180-angleThreshold) || yaw <= (-180+angleThreshold)){
      return 2;
    } else if ((-90-angleThreshold) <= yaw && yaw <= (-90+angleThreshold)){
      return 3; 
    } else if((0+angleThreshold) >= yaw && yaw >= (0-angleThreshold)){
      return 4;  
    } else {
      return 0;  
    }
  }
  
