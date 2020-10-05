byte counter = 0;
uint8_t value; 
const int A1A = 2;//define pin 2 for A1A
const int A1B = 3;//define pin 3 for A1B
const int POTMETERPIN = A0;

void setup() {
  Serial.begin(9600); 
  pinMode(A1A,OUTPUT);
  pinMode(A1B,OUTPUT);  

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
    digitalWrite(A1A,LOW);
  } else{
  if (counter == 0){
    digitalWrite(A1A,HIGH);
  }
  if(counter > value){
    digitalWrite(A1A,LOW);
    }
  }
}

void loop() {
  if (Serial.available() > 0) {
    String incomingByte = Serial.readString();
    int number = incomingByte.toInt(); 

    if(number == 33 || number == 45 || number == 78){
    value = map(number, 0, 167, 0, 255);
    Serial.println(value); 
    delay(2000); 
    } else{
      Serial.println("Dit is een illegale waarde"); 
    }
  }
}
