/*
  Writepins234
*/

int val=0;
int pin=0;

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.println("Hallo");
  
}

void loop() {
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();      // read the incoming byte:
    Serial.write(incomingByte);
    if (incomingByte==104) {
      digitalWrite(2,HIGH);
    }
    if (incomingByte==111) {
      digitalWrite(3,HIGH);
    }
    if (incomingByte==105) {
      digitalWrite(4,HIGH);
    }
    if (incomingByte==72) {
      digitalWrite(2,LOW);
    }
    if (incomingByte==79) {
      digitalWrite(3,LOW);
    }
    if (incomingByte==73) {
      digitalWrite(4,LOW);
    }
  }
}
