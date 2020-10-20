byte counter = 0;
uint8_t value;
const int SERVO = 3;
const int POTMETERPIN = A0; 
int potmeterValue = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(SERVO, OUTPUT); 

  cli(); 

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
  if(value == 0){
    digitalWrite(SERVO, LOW); 
  } else{
  if (counter == 0){
    digitalWrite(SERVO,HIGH);
  }
  if(counter > value){
    digitalWrite(SERVO,LOW);
    }
  }
}

void loop() {
  potmeterValue = analogRead(POTMETERPIN);
  value = map(potmeterValue, 0, 1023, 0, 255);
  Serial.println(value);
}
