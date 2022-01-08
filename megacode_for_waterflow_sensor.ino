
#include <Wire.h>; 

int flowPin = 2;
double flowRate;
volatile int count;
unsigned long oldTime;

int bell = 49;
int valve = 13;
int waterLevel = A0;
 
 
void setup() {
  pinMode(bell, OUTPUT);
  pinMode(valve, OUTPUT);
  pinMode(waterLevel, INPUT);
  Serial.begin(9600); 
  pinMode(flowPin, INPUT);
  attachInterrupt(0,flow,FALLING);
}
 
void loop() {
  
  if (millis() - oldTime > 2000){ // baca sinyal pulse setiap 10 milli second
    detachInterrupt(0);   // non aktifkan interuptsi
    oldTime = millis(); // update waktu internal
    count = 0;
    //count--;
    attachInterrupt(0,flow,FALLING); // aktifkan lagi interruptsi
  }  
  Serial.println(analogRead(waterLevel));
  if(count > 5) {
    digitalWrite(bell, HIGH);
    analogWrite(valve, 255);
  }
  else {
    digitalWrite(bell, LOW);
    analogWrite(valve, 0);
  }
  while(analogRead(waterLevel) > 500) {
    analogWrite(valve, 255);
  }
}
 
void flow(){
  count++; // counter jika ada sinyal FALLING di pin 2 ( int0 )
}
