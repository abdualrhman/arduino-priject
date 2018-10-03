#include <SPI.h>
#include <WiFi.h>
//#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {0x90, 0xA2, 0xDA, 0x0D, 0x1D, 0xB5};
IPAddress ip(10, 26, 101, 153);
char server[] = "influx.itu.dk";

char ssid[] = "sensors";
//char pass[] = "oqjy0663";
char pass[] = "n0n53n53";
int status = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned long lastMillis = 0;

//declear button pins
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;

int button1State, button2State, button3State;

// declear LED pins
int callMe_led = 5;
int goToLuch_led = 6;
int comeHere_led = 8;
// ledState  to set the LED


int ledState = LOW;             // ledState  to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

const long interval = 150;  

void ledFunc(int ledPin){
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(ledPin, LOW);
}

 


// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);


void callMe(){
  Serial.println("callMe");
  ledFunc(callMe_led);
}

void goToLunch(){
  Serial.println("goToLuch");
  ledFunc(goToLuch_led);
}
void comeHere(){
  Serial.println("goToLuch");
  ledFunc(comeHere_led);
}


// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Recieved Message!");
  Serial.println(payload[0]);
  if(payload[0] == 54){
    goToLunch();
   }
   if(payload[0] == 55){
    callMe();
   }
   if(payload[0] == 56){
    comeHere();
   }
}


void setup()
{
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

 while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 7 seconds for connection:
    delay(7000);
  }

  if (client.connect("ino_2","lock", "fah6eeroMaewieg1Ahqu9kaifohSho")) {
    Serial.println("MQTT Connected");
    //startFunc();
    client.subscribe("topic/test");
  }else{
    Serial.println(client.state());
  }
}
void loop()
{
   button1State = digitalRead(button1Pin);
   button2State = digitalRead(button2Pin);
   button3State = digitalRead(button3Pin);

   if(button1State == LOW){
        client.publish("topic/test", "1");
        delay(1000);
   }
   if(button2State == LOW){
        client.publish("topic/test", "2");
        delay(1000);
   }
   if(button3State == LOW){
        client.publish("topic/test", "3");
        delay(1000);
   }
   client.loop();
}
