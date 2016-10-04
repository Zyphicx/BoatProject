const int TRANS = 4;
const int MOTOR = 6;

const int powerTwo = 6;

void setup() {
  pinMode(TRANS, INPUT);
  pinMode(MOTOR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    if(digitalRead(TRANS) == HIGH){
      delayMicroseconds(1500);
      int signalValue = getSignal(TRANS);
      Serial.print("Value: ");
      Serial.println(signalValue);
      Serial.println("-----------");
      if(signalValue == 5){
        analogWrite(MOTOR, 255);
        delay(25);
      }else{
        analogWrite(MOTOR, 100);
      }
    }else{
      analogWrite(MOTOR, 100);  
    }
}

int getSignal(int pin){
  int value = 0;
  int i;
  int power = 1;
  
  for(i = 0; i < powerTwo; i++){
    int pulseState = digitalRead(pin);
    //Serial.println(pulseState);
    value += power * pulseState;
    power *= 2;
    delay(1);
  }
  return value;
}
