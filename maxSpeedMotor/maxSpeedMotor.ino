#define dirPin 2
#define dirPin2 4
#define stepPin 3
#define stepPin2 5
#define ms 6
#define ms2 7
#define ms3 8
#define ms4 9
#define stepsPerRevolution 200

void setup() {
   pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  
  pinMode(ms, HIGH); 
  pinMode(ms2, HIGH); 
  pinMode(ms3, HIGH); 
  pinMode(ms4, HIGH); 

}

void loop() {

    digitalWrite(dirPin, HIGH); 
    digitalWrite(dirPin2, LOW); 
     digitalWrite(stepPin, HIGH);
  digitalWrite(stepPin2, HIGH);
  delayMicroseconds(365);
  digitalWrite(stepPin, LOW);
  digitalWrite(stepPin2, LOW);
  delayMicroseconds(365);
}
