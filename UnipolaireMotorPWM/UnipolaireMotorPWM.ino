#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

#define triggerPin 2
#define echoPin 3
int step_number = 0;
long cm; 
long duration; 
bool gotSensored = false; 
int RPM = 0; 
byte counter = 0;
byte counter2 = 0; 
uint8_t value; 

void setup() {
  Serial.begin(9600); 
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  cli(); 
  
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0  = 0;
  OCR0A = 124;
  TCCR0A |= (1 << WGM01);
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  TIMSK0 |= (1 << OCIE0A);

  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 249;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS20);   
  TIMSK2 |= (1 << OCIE2A);

  sei();
}
ISR(TIMER2_COMPA_vect){
  counter++; 
  if (counter == 0){
     OneStep(); 
  } 
}
ISR(TIMER0_COMPA_vect){
}

void loop() {
  Serial.print(" TOTAL SENSOR "); 
  Serial.println(RPM); 
  if(cm < 5 && !gotSensored){
    gotSensored = true; 
    RPM++; 
  } else if(cm > 25 && gotSensored && step_number!=0){
    gotSensored = false; 
  }
//  OneStep();
//  delayMicroseconds(2500);
    cm = getDistanceInCM();
    Serial.println(cm); 
}


void OneStep(){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
int getDistanceInCM() {
  // Zend een geluid met hoge frequentie uit. 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Meet hoe lang het duurt voor het geluid terug is.
  duration = pulseIn(echoPin, HIGH); 
  // Bereken de centimeters op basis van de tijd.
  return (duration/2) / 29.1;  
}
