// COMP-10184 – Mohawk College 
// ALARM SYSTEM 
//  
// Simulates a real work motin detecting alarm system
// 
// @author  NOLAN CARTER 
// @id   000817341 
// 
// I created this work and I have not shared it with anyone else. 
//
 
#include <Arduino.h> 
 
// digital input pin definitions 
#define PIN_PIR D5 
#define PIN_BUTTON D6

int brightness = 255;
bool motionDetected = false;

void stageOne(){
  if (digitalRead(PIN_PIR)){
    digitalWrite(LED_BUILTIN,LOW);
    delay(10000);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
  }
}

void stageTwo(){
  if (digitalRead(PIN_PIR)){
    int i;

    for (i=0;i<40;i++){
      digitalWrite(LED_BUILTIN,LOW);
      delay(125);
      digitalWrite(LED_BUILTIN,HIGH);
      delay(125);
    }
  }
}

void stageThree(){
  if (digitalRead(PIN_PIR) && !motionDetected){
    int i;

    for (i=0;i<40;i++){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(125);
      digitalWrite(LED_BUILTIN,LOW);
      delay(125);
    }
    motionDetected = true;
  }
}

void stageFour(){
  if (digitalRead(PIN_PIR) && !motionDetected){
    unsigned long startTime = millis();
    unsigned long endTime = startTime;

    motionDetected = true;
    while (endTime - startTime <= 5000)
    { 
      if (digitalRead(PIN_BUTTON) == 0)
      {
        motionDetected = false;
        digitalWrite(LED_BUILTIN,HIGH);
        break;
      }

      if ((endTime - startTime)%1000 == 0 
      || (endTime - startTime)%1000 == 250 
      || (endTime - startTime)%1000 == 500 
      || (endTime - startTime)%1000 == 750)
      {
        digitalWrite(LED_BUILTIN,LOW);
      }
      if ((endTime - startTime)%1000 == 125 
      || (endTime - startTime)%1000 == 375 
      || (endTime - startTime)%1000 == 625 
      || (endTime - startTime)%1000 == 875)
      {
        digitalWrite(LED_BUILTIN,HIGH);
      }
      
      endTime = millis();
      Serial.println((endTime - startTime));
    }
    
  }
}

void stageFive(){
  if (digitalRead(PIN_PIR) && !motionDetected){
    unsigned long startTime = millis();
    unsigned long endTime = startTime;

    motionDetected = true;
    while (endTime - startTime <= 10000)
    { 
      if (digitalRead(PIN_BUTTON) == 0)
      {
        digitalWrite(LED_BUILTIN,HIGH);
        break;
      }

      if ((endTime - startTime)%1000 == 0 
      || (endTime - startTime)%1000 == 250 
      || (endTime - startTime)%1000 == 500 
      || (endTime - startTime)%1000 == 750)
      {
        digitalWrite(LED_BUILTIN,LOW); // turn LED on
      }

      if ((endTime - startTime)%1000 == 125 
      || (endTime - startTime)%1000 == 375 
      || (endTime - startTime)%1000 == 625 
      || (endTime - startTime)%1000 == 875)
      {
        digitalWrite(LED_BUILTIN,HIGH); // turn LED off
      }
      
      endTime = millis();
      Serial.println((endTime - startTime));
    }
  }
  else if (motionDetected && digitalRead(PIN_BUTTON) == 0)
  {
    motionDetected = false;
  }
  
}
 
 
// ************************************************************* 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // configure the LED output 
  pinMode(LED_BUILTIN, OUTPUT); 
 
  // PIR sensor is an INPUT 
  pinMode(PIN_PIR, INPUT); 
 
  // Button is an INPUT 
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // start LED off
  digitalWrite(LED_BUILTIN,HIGH);
} 
 
// ************************************************************* 
void loop() { 

  // stageOne();

  // stageTwo();

  // stageThree();

  // stageFour();

  stageFive();
} 