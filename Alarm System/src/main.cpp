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
#define STEP_ZERO 0
#define STEP_ONE 125
#define STEP_TWO 250
#define STEP_THREE 375
#define STEP_FOUR 500
#define STEP_FIVE 675
#define STEP_SIX 750
#define STEP_SEVEN 875

bool motionDetected = false;
unsigned long startTime;
unsigned long elapsedTime;

// *********************************************************** 
// Flashes built in LED 4 times per second for 10 seconds if movement is detected
// Button will deactivate the blinking light 
// 
void stageFive(){
  if (digitalRead(PIN_PIR) && !motionDetected){
    startTime = millis();
    elapsedTime = startTime;
    motionDetected = true;

    while (elapsedTime - startTime <= 10000)
    { 
      if (digitalRead(PIN_BUTTON) == 0)
      {
        digitalWrite(LED_BUILTIN,HIGH); // turns LED off
        break;
      }

      // turns LED on four times a second
      if ((elapsedTime - startTime)%1000 == STEP_ZERO 
      || (elapsedTime - startTime)%1000 == STEP_TWO 
      || (elapsedTime - startTime)%1000 == STEP_FOUR 
      || (elapsedTime - startTime)%1000 == STEP_SIX)
      {
        digitalWrite(LED_BUILTIN,LOW); // turn LED on
      }

      // turns LED off 4 times a second
      if ((elapsedTime - startTime)%1000 == STEP_ONE
      || (elapsedTime - startTime)%1000 == STEP_THREE
      || (elapsedTime - startTime)%1000 == STEP_FIVE
      || (elapsedTime - startTime)%1000 == STEP_SEVEN)
      {
        digitalWrite(LED_BUILTIN,HIGH); // turn LED off
      }
      
      elapsedTime = millis(); // sets new elapsedTime
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
  stageFive();
} 