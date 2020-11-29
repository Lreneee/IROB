#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#include <Adafruit_NeoPixel.h>
const int ledPin = 0; 

const char* ssid = "Wifi van de buren Boven";
const char* wifi_password = "Syntax420";

const char* mqtt_server = "192.168.2.2";
const char* mqtt_topic = "Motor";
const char* mqtt_username = "username";
const char* mqtt_password = "Driehoek";

const char* clientID = "ESP8266_1";

const int A1A = 5;//define pin 2 for A1A
const int A1B = 4;//define pin 3 for A1B
#define LEDPIN 15
#define LEDCOUNT 5
Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_GRB + NEO_KHZ800);

bool colorVisible = false; 

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void ReceivedMessage(char* topic, byte* payload, unsigned int length) {
  Serial.println((char)payload[0]);

  if ((char)payload[0] == '0') {
     motorA('R');// Turn motor A to RIGHT
     delay(500); 
     motorA('O');// Turn motor A OFF
     delay(1000); 
     if(!colorVisible){
     strip.setPixelColor(2, 255, 0, 255); 
     strip.show(); 
     colorVisible=true; 
     Serial.println("visible"); 
     } else if(colorVisible){
     colorVisible = false; 
     strip.setPixelColor(2, 255, 0, 0); 
     strip.show(); 
     Serial.println("not visible"); 
     }
  }
  if ((char)payload[0] == '1') {
    Serial.println("ja sorry"); 
  }
}

bool Connect() {
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
      client.subscribe(mqtt_topic);
      return true;
    }
    else {
      return false;
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  strip.begin();
  
  pinMode(A1A,OUTPUT);
  pinMode(A1B,OUTPUT);  

  digitalWrite(ledPin, HIGH);

  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setCallback(ReceivedMessage);
  if (Connect()) {
    Serial.println("Connected Successfully to MQTT Broker!");  
  }
  else {
    Serial.println("Connection Failed!");
  }
}

void loop() {

  strip.clear(); 
  if (!client.connected()) {
    Connect();
  }
  client.loop();
}

void motorA(char d)
{
  if(d =='R'){
    digitalWrite(A1A,LOW);
    digitalWrite(A1B,HIGH); 
  }else if (d =='L'){
    digitalWrite(A1A,HIGH);
    digitalWrite(A1B,LOW);    
  }else{
    //Robojax.com L9110 Motor Tutorial
    // Turn motor OFF
    digitalWrite(A1A,LOW);
    digitalWrite(A1B,LOW);    
  }
}
