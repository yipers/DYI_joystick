#include <Joystick.h>

// Used this joystick lib
// https://github.com/AM-STUDIO/Analog-E-Brake

void setup() {
  // put your setup code here, to run once:
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    Joystick.begin();
}

// Hardware pin mapping
const int pinToButtonMap1 = A0;
const int pinToButtonMap2 = A1;

// Runtime variables
int counter = 0;
int avg = 0;

// Modifier constant params
const int sliderLowerLimit = 3;
const int sliderLimit = 254;
const int analogMultiplier = 10;

void loop() {
  int pot1 = analogRead(A0) * analogMultiplier;
  int pot2 = analogRead(A1) * analogMultiplier;
  int mapped = map(((pot1 + pot2) / 2), 10, 1023, 0,255);

  if(mapped > sliderLimit){
    mapped = sliderLimit;  
  } else if(mapped <= sliderLowerLimit) {
    mapped = 0;  
  }

  if(mapped <= sliderLowerLimit) {
    Joystick.setThrottle(0);
  } else if(counter == 3) {
    if(avg > sliderLimit){
      avg = sliderLimit;  
    }
    
    counter = 0;
    Joystick.setThrottle(avg);
    avg = 0;
  } else {
    counter++;
    avg = avg + mapped;
  }

    

  // For debugging
  /*Joystick.setThrottle(mapped);
  Serial.println((String)"pot1: " + pot1);
  Serial.println((String)"pot2: " + pot2);
  Serial.println((String)"mapped: " + mapped);
  Serial.println((String)"------------------");*/
}
