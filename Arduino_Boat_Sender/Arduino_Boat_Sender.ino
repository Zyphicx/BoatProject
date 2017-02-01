struct{
  const int PIN;
  const int VALUE;  
} LEDS[] = {4, 6,
           7, 5};
const int powerTwo = 6;
const int maxPower = 32;

int randomValue;

void setup() {
  int i;
  for(i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++){
    pinMode(LEDS[i].PIN, OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  int i;
  for(i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++){
    int sig[powerTwo];
    int valueToSend = LEDS[i].VALUE;
    //Serial.println(valueToSend);
    valueToSignal(valueToSend, sig);
    sendSignal(LEDS[i].PIN, sig);
    delay(1);
  }
  delay(15);
}

void sendSignal(int pin, int *sig){
  digitalWrite(pin, HIGH);
  delay(1);
  Serial.print(pin);
  Serial.print(" - ");
  for(int i = 0; i < powerTwo; i++){
      Serial.print(sig[i]);
      digitalWrite(pin, sig[i]);
      delay(1);
  }
  Serial.println();
  digitalWrite(pin, LOW);
}

void valueToSignal(int value, int *sig){
  int power;
  int i = powerTwo - 1;
  
  for(power = maxPower; power >= 1; power /= 2){
    value -= ((sig[i--] = ((int) value / power)) ? power : 0);
  }
}
