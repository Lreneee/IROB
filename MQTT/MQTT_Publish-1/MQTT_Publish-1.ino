#include <Bounce2.h> 
#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 15
#define RST_PIN 16
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int ledPin = 0; 
const int buttonPin = 5;  

const char* ssid = "Wifi van de buren Boven";
const char* wifi_password = "Syntax420";

const char* mqtt_server = "192.168.2.2";
const char* mqtt_topic = "Your Topic";
const char* mqtt_username = "username";
const char* mqtt_password = "Driehoek";

const char* clientID = "Client ID";
const char* string; 

Bounce bouncer = Bounce();

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(ledPin, HIGH);

  SPI.begin();    
  mfrc522.PCD_Init();  

  bouncer.attach(buttonPin);
  bouncer.interval(5);

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

  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
  
}

void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content = ""; 
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println(content); 
  string = content.c_str(); 
  client.publish(mqtt_topic, string); 
  delay(2000); 
}
