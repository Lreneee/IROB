
int potPin = A0;   
int ledPin = 13;  
int val = 0;      
int newVal = 0;
int difference = 0;  
String offset = "Hoog"; 

void setup() {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);  
}

void loop() {
   val = analogRead(potPin);
  if(val > 510 && offset!="Hoog"){
    Serial.println("Hoog"); 
    offset = "Hoog";
  } else if(val <490 && offset!="Laag"){
    Serial.println("Laag"); 
    offset = "Laag";
   }   
   
  Serial.println(analogRead(potPin)); 
  newVal = analogRead(potPin); 
  difference = newVal - val; 
  digitalWrite(ledPin, HIGH);  
  delay(val);                  
  digitalWrite(ledPin, LOW);  
  delay(val);                  
}
 
