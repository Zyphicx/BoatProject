const int LED = 4;
const int powerTwo = 6;
const int maxPower = 32;

int randomValue;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int sig[powerTwo];
  int valueToSend = 5;
  Serial.println(valueToSend);
  valueToSignal(valueToSend, sig);
  sendSignal(LED, sig);
  delay(50);
}

void sendSignal(int pin, int *sig){
  digitalWrite(pin, HIGH);
  delay(1);
  for(int i = 0; i < powerTwo; i++){
      digitalWrite(pin, sig[i]);
      delay(1);
  }
  digitalWrite(pin, LOW);
}

void valueToSignal(int value, int *sig){
  int power;
  int i = powerTwo - 1;
  
  for(power = maxPower; power >= 1; power /= 2){
    value -= ((sig[i--] = ((int) value / power)) ? power : 0);
  }
}
