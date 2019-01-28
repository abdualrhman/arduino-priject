// board_1
#include "SerialMP3Player.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
// Connect to the WiFi
//"AndroidAP9921"
const char* ssid = "sensors"; //fill in the network name
const char* password = "n0n53n53"; //fill in the password
const char* mqtt_server = "influx.itu.dk"; 
 
WiFiClient espClient;
PubSubClient client(espClient);

//define TX and RX for Serial mp3 player
#define TX D7
#define RX D8

SerialMP3Player mp3(RX,TX);

// configuring button's press length
float pressLength_milliSeconds = 0;
int goToLunch_milliSeconds = 100;
int comeHere_milliSeconds = 2000; 

 // configuring button's pin
int buttonPin = D5;

 // configuring LED's pins
int const_LED_pin = D7;
int func_ledPin = D6;

//configuation for const_LED_func 
int ledState = LOW;
long previousMillis = 0;
long interval = 1000;

// constant LED function 
void const_LED_func(){
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(const_LED_pin, ledState);
  }  
}

// red LED function 
void ledFunc(){
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(125);
    digitalWrite(func_ledPin, LOW);
    delay(125);
    digitalWrite(func_ledPin, HIGH);
    delay(3000);
    digitalWrite(func_ledPin, LOW);
}

void goToLunch(){
  Serial.println("goToLuch");
  mp3PlayerFunc(1);
  ledFunc();
}
void comeHere(){
  Serial.println("come here");  
  mp3PlayerFunc(2);
  ledFunc();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Recieved Message!");
  Serial.println(payload[0]);
   if(payload[0] == 50){
    comeHere();
   }
  if(payload[0] == 49){
    goToLunch();
   }
}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Attempt to connect
 if (client.connect("ino_1","lock", "fah6eeroMaewieg1Ahqu9kaifohSho")) {
  Serial.println("connected");
  // ... and subscribe to topic
  client.subscribe("topic/test");//subscribe to topic/test 
 } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
  }
 }
}


void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);     
 
  pinMode(const_LED_pin, OUTPUT); 
  pinMode(func_ledPin, OUTPUT); 
  
 Serial.begin(115200);
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 delay(250);
 //select sd-card for Serial mp3 player 
 mp3.sendCommand(CMD_SEL_DEV, 0, 2);   
 delay(250); 
}
void loop()
{
 if (!client.connected()) {
  reconnect();
 }

 if(client.connected()){const_LED_func();}
  
  while (digitalRead(buttonPin) == LOW ){ 
    delay(100);  
    pressLength_milliSeconds = pressLength_milliSeconds + 100;   
    yield();
  }
  if (pressLength_milliSeconds >= comeHere_milliSeconds){

       client.publish("topic/test", "3");
  }
  else if(pressLength_milliSeconds >= goToLunch_milliSeconds){
    
       client.publish("topic/test", "4");
  }
  pressLength_milliSeconds = 0;  
 client.loop();
}

// mp3 player function 
void mp3PlayerFunc(int type){
  if(type == 1){
     mp3.play(00000001); 
    delay(1000);
    mp3.stop();
  }
  else if (type == 2){
    mp3.play(00000002); 
    delay(1000);
    mp3.stop();
  }
}
