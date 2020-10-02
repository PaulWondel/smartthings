// Variables:
int S1 = 2;           // Variable to store the value read from the sensor pin
int S2 = 3; 
int S3 = 4;
int Val1;
int Val2;
int Val3;

//VOID SETUP
void setup() {
 pinMode(S1, INPUT);  // Declare pin as INPUT
 pinMode(S2, INPUT);
 pinMode(S3, INPUT);
 
 Serial.begin(9600); // Define serial port
}


//VOID LOOP
void loop() {
  
// Serial.print = Write the binairy value 0/1
// Serial.write = Write the translated value according to ASCII tabel
  
Val1 = digitalRead(S1); //Read variables. Digitaal i.e.: 1/0
if (Val1 == 0) {
  Serial.write (104);} //h
  if (Val1 == 1) {
  Serial.write (72);}  //H

Val2 = digitalRead(S2);
if (Val2 == 0) {
  Serial.write (111);}  //o
if (Val2 == 1) {
  Serial.write (79);}   //O

Val3 = digitalRead(S3);
if (Val3 == 0) {
  Serial.write (105);   //i
  Serial.write (10);}   //carriage return
if (Val3 == 1) {
  Serial.write (73);    //I
  Serial.write (10);}   //carriage return
 
  // Delay
  delay(1000);          // delay to avoid overloading the serial port buffer
}
