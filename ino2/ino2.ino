// board_2
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
// Connect to the WiFi
const char* ssid = "AndroidAP9921"; //fill in the network name
const char* password = "*******"; //fill in the password
const char* mqtt_server = "influx.itu.dk"; 
 
WiFiClient espClient;
PubSubClient client(espClient);

float pressLength_milliSeconds = 0;
 
int goToLunch_milliSeconds = 100;
int comeHere_milliSeconds = 2000;        
 
int buttonPin = D5;
 

// declear LED pins
int const_LED_pin = D7;
int func_ledPin = D6;

int ledState = LOW;
long previousMillis = 0;
long interval = 1000;

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

void ledFunc(){
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(250);
    digitalWrite(func_ledPin, LOW);
    delay(250);
    digitalWrite(func_ledPin, HIGH);
    delay(3000);
    digitalWrite(func_ledPin, LOW);
}


void goToLunch(){
  Serial.println("goToLuch");
  ledFunc();
}

void comeHere(){
  Serial.println("come here");  
  ledFunc();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Recieved Message!");
  Serial.println(payload[0]);
   if(payload[0] == 51){
    comeHere();
   }
  if(payload[0] == 52){
    goToLunch();
   }
}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Attempt to connect
 if (client.connect("arduino_2","lock", "fah6eeroMaewieg1Ahqu9kaifohSho")) {
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
 
}
void loop()
{
 if (!client.connected()) {
  reconnect();
 }
 // if the devide is connected to the network start the const_LED_func
 if(client.connected()){const_LED_func();}
 buttonClicking();
 client.loop();
}

void buttonClicking(){
 while (digitalRead(buttonPin) == LOW ){ 
    delay(100);  
    pressLength_milliSeconds = pressLength_milliSeconds + 100;   
    
  }
  if (pressLength_milliSeconds >= comeHere_milliSeconds){

       client.publish("topic/test", "1");


  } 
  else if(pressLength_milliSeconds >= goToLunch_milliSeconds){
        client.publish("topic/test", "2");



  }
  pressLength_milliSeconds = 0;  
}

