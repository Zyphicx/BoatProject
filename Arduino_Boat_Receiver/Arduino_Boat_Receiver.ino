struct{ //A structure for each side of the boat
  const int TRANSPIN;
  const int MOTORPIN;
  int SIGNALS[10];
  int curSig;
} RCVS[] = {4, 6, {2, 3, 4}, 2,
            5, 7, {5, 6, 7}, 5};

const int powerTwo = 6;

const int buttonPin = 11;
int route = 1;

void setup() {
  int i;
  for(i = 0; i < sizeof(RCVS) / sizeof(RCVS[0]); i++){
    pinMode(RCVS[i].TRANSPIN, INPUT);
    pinMode(RCVS[i].MOTORPIN, OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); //YOU SHOULD PROBABLY REMOVE THIS PIECE OF CODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void loop(){
    if(digitalRead(buttonPin) == HIGH)
        route = (route ? 0 : 1);
    digitalWrite(); //MODIFY THIS TO CHANGE THE DIRECTION THAT THE MOTOR IS GOING IN (YOU COULD ALSO JUST CHANGE IT IN THE IF-STATEMENT)
    digitalWrite();
    
    int i;
    for(i = 0; i < sizeof(RCVS) / sizeof(RCVS[0]); i++){
      if(digitalRead(RCVS[i].TRANSPIN) == HIGH){
        delayMicroseconds(1500);
          int signalValue = getSignal(RCVS[i].TRANSPIN);
          Serial.print("Value: ");         //AND ALL OF THESE LINES OF CODE!!!!!!!!!!!!!!!!
          Serial.println(signalValue);
          Serial.println("-----------");
          if(contains(RCVS[i].SIGNALS, signalValue, sizeof(RCVS[i].SIGNALS) / sizeof(RCVS[0].SIGNALS[0])) && signalValue >= RCVS[i].curSig){
            Serial.println("Running"); // AND THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if(signalValue > RCVS[i].curSig)
              RCVS[i].curSig = signalValue;
            analogWrite(RCVS[i].MOTORPIN, 255);
            delay(50);
          }else{
            analogWrite(RCVS[i].MOTORPIN, 150); //CHANGE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          }
       }else{
        analogWrite(RCVS[i].MOTORPIN, 150); //CHANGE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
