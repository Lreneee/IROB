
int potPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor
int newVal = 0;
int difference = 0;  
String offset = "Hoog"; 

void setup() {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
}

void loop() {
   val = analogRead(potPin);
  if(val > 510 && offset!="Hoog"){
    Serial.println("Hoog"); 
    offset = "Hoog";
  } else if(val <490 && offset!="Laag"){
    Serial.println("Laag"); 
    offset = "Laag";
   }    // read the value from the sensor
  Serial.println(analogRead(potPin)); 
  newVal = analogRead(potPin); 
  difference = newVal - val; 
  digitalWrite(ledPin, HIGH);  // turn the ledPin on
  delay(val);                  // stop the program for some time
  digitalWrite(ledPin, LOW);   // turn the ledPin off
  delay(val);                  // stop the program for some time
}
 
