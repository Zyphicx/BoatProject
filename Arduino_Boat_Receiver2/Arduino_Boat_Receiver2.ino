struct{ //A structure for each side of the boat
  const int TRANSPIN;
  const int MOTORPIN;
  int STEER1;
  int STEER2;
  int SIGNALS[10];
  int curSig;
} RCVS[] = {12, 9, 3, 2, {2, 3, 4}, 2,
            13, 10, 7, 6, {5, 6, 7}, 3};

const int powerTwo = 6;

const int buttonPin = 11;
int route = 1;

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

void setup() {
  int i;
  for(i = 0; i < sizeof(RCVS) / sizeof(RCVS[0]); i++){
    pinMode(RCVS[i].TRANSPIN, INPUT);
    pinMode(RCVS[i].MOTORPIN, OUTPUT);
    pinMode(RCVS[i].STEER1, OUTPUT);
    pinMode(RCVS[i].STEER2, OUTPUT);
    digitalWrite(RCVS[i].STEER1, HIGH);
  }
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);
}

void loop(){
  if(digitalRead(buttonPin) == HIGH)
    route = (route ? 0 : 1);
  
  int i;
  for(i = 0; i < sizeof(RCVS) / sizeof(RCVS[0]); i++){
    digitalWrite(RCVS[i].STEER1, route);
    digitalWrite(RCVS[i].STEER2, !route);
    
    Serial.println(digitalRead(RCVS[i].TRANSPIN));
      if(digitalRead(RCVS[i].TRANSPIN) == HIGH){
        delayMicroseconds(1500);
        int signalValue = getSignal(RCVS[i].TRANSPIN);
        Serial.print("Value: ");
        Serial.println(signalValue);
        Serial.println("-----------");
        if(contains(RCVS[i].SIGNALS, signalValue, sizeof(RCVS[i].SIGNALS) / sizeof(RCVS[0].SIGNALS[0])) && signalValue >= RCVS[i].curSig){
          Serial.println("Running");
          Serial.print(RCVS[i].MOTORPIN);
          if(signalValue > RCVS[i].curSig){
             RCVS[i].curSig = signalValue;
          }
          analogWrite(RCVS[i].MOTORPIN, 255);
          delay(1000);
        }else{
          analogWrite(RCVS[i].MOTORPIN, 160); //CHANGE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
      }else{
        analogWrite(RCVS[i].MOTORPIN, 160); //CHANGE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      }
  }
  delay(15);
}
