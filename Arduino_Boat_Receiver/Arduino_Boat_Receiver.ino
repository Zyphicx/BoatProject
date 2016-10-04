struct{ //A structure for each side of the boat
  const int TRANSPIN;
  const int MOTORPIN;
} RCVS[] = {4, 6};

const int powerTwo = 6;

void setup() {
  pinMode(RCVS[0].TRANSPIN, INPUT);
  pinMode(RCVS[0].MOTORPIN, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int i;
  for(i = 0; i < sizeof(RCVS) / sizeof(RCVS[0]); i++){
      if(digitalRead(RCVS[i].TRANSPIN) == HIGH){
        delayMicroseconds(1500);
        int signalValue = getSignal(RCVS[i].TRANSPIN);
        Serial.print("Value: ");
        Serial.println(signalValue);
        Serial.println("-----------");
        if(signalValue == 5){
          analogWrite(RCVS[i].MOTORPIN, 255);
          delay(25);
        }else{
          analogWrite(RCVS[i].MOTORPIN, 100);
        }
      }else{
        analogWrite(RCVS[i].MOTORPIN, 100);  
      }
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
