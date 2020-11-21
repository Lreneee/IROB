byte counter = 0;
uint8_t value; 
#define A        2                     // the pin connected to the wire A of the coil A (or to the H-bridge pin controlling the same wire) 
#define A_bar    3                     // the pin connected to the wire A- of the coil A (or to the H-bridge pin controlling the same wire)
#define B        4                     // the pin connected to the wire B of the coil A (or to the H-bridge pin controlling the same wire)
#define B_bar    5                     // the pin connected to the wire B- of the coil A (or to the H-bridge pin controlling the same wire)
#define POTMETERPIN A0
int potmeterValue = 0;
int stepsPerRevolution = 0; 
float delay_time;
int value_potentiometer = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(A, OUTPUT);
  pinMode(A_bar, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(B_bar, OUTPUT);

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
      
  } else{
  if (counter == 0){
  }
  if(counter > value){
    
    }
  }
}

void loop() {  
  potmeterValue = analogRead(POTMETERPIN);
  value = map(potmeterValue, 0, 1023, 0, 255);
  stepper(); 
  delayMicroseconds(100000); 
}
void stepper(){
    switch(stepsPerRevolution){
    case 0:
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, LOW);
    break; 
    case 1: 
    digitalWrite(A, LOW);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    break; 
    case 2:
    digitalWrite(A, LOW);
    digitalWrite(A_bar, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, LOW);
    break; 
    case 3:
    digitalWrite(A, LOW);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    break; 
  }
  stepsPerRevolution++;
  if(stepsPerRevolution > 3){
    stepsPerRevolution = 0;
  }
}
