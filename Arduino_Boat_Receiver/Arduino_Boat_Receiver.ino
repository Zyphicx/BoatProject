struct{ //A structure for each side of the boat 
  const int TRANSPIN;
  const int MOTORPIN;
  int SIGNALS[10];
  int curSig;
} RCVS[] = {4, 6, {5, 6}, 2};

const int powerTwo = 6;

void setup() {
  int i;
  for(i = 0; i < sizeof(RCVS) / sizeof(RCVS[0]); i++){
    pinMode(RCVS[i].TRANSPIN, INPUT);
    pinMode(RCVS[i].MOTORPIN, OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  int i;
  for(i = 0; i < sizeof(RCVS) / sizeof(RCVS[0]); i++){
      if(digitalRead(RCVS[i].TRANSPIN) == HIGH){
        delayMicroseconds(1500);
        int signalValue = getSignal(RCVS[i].TRANSPIN);
        /*Serial.print("Value: ");
        Serial.println(signalValue);
        Serial.println("-----------");*/
        if(contains(RCVS[i].SIGNALS, signalValue, sizeof(RCVS[i].SIGNALS) / sizeof(RCVS[0].SIGNALS[0])) && signalValue >= RCVS[i].curSig){
          if(signalValue > RCVS[i].curSig)
             RCVS[i].curSig = signalValue;
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

int contains(int *arr, int num, int arrSize){
  int i;
  for(i = 0; i < arrSize; i++)
    if(arr[i] == num)
      return i + 1;
  return 0;
}
