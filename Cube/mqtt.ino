const char* MQTT_CLIENT = "64k_node_";
char MQTT_CLIENT_ID[20];
const char* MQTT_SENSOR_TOPIC = "64k/ping";
const char* MQTT_SERVER_IP = "iot.muid.sh";
const uint16_t MQTT_SERVER_PORT = 1883;

void setup_mqtt(){
  createMqttId();
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.setCallback(onMessage);  
}

void createMqttId(){
  char myID[32];
  sprintf(myID, "%d", ID);
  strcpy(MQTT_CLIENT_ID,MQTT_CLIENT);
  strcat(MQTT_CLIENT_ID,myID);
}

void mqtt_Update(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();  
}

void reconnect() {
  Serial.println("INFO: Connecting to MQTT-Server");
  while (!client.connected()) {
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID)) {
      Serial.println("INFO: MQTT connected");
      Serial.println();
      client.subscribe(MQTT_SENSOR_TOPIC, 1);
    } else {
      led.setColor(255,0,0);
      led.on();
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 seconds");
      // Wait 5 seconds before retrying
      delay(500);
      led.setColor(0,0,255);
      delay(500);
    }
  }
}

void onMessage(char* topic, byte* payload, unsigned int length) {
  Serial.println("INFO: RECEIVED");
  Serial.println("Topic: " + String(topic));  
  
  //full payload would be: 1,11,14k_node_1
  String data = String((char*) payload).substring(0,length);

  int index = data.indexOf(",");
  String id = data.substring(0, index);

  if (id == String(ID)) return;
  
  Serial.println("ID  : " + id);
  Serial.println();

  // Switch on the LED if another party has send a new status
  Serial.println("Got command");
  Serial.println();

  int status = data.substring(index + 1).toInt();
  newState = true;
  motor.startWigwag();
}

void sendStatus(int status) {
  char buffer[32];
  sprintf(buffer, "%i,%i", ID, status);
  Serial.println("INFO: SENDING");
  Serial.println("Data: " + String(buffer));
  Serial.println();
  client.publish(MQTT_SENSOR_TOPIC, buffer);
}
