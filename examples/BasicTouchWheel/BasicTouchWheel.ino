/*
  Basic Touch Wheel

  This uses a ring of capacitive insulated touch pads in a wheel configuration. 
  Three pins are used, and the corresponding pads can be repeated 
  any number of times for higher resolution touch wheels. 

  E.g.: repeating the pad sequence: 1,2,3,1,2,3,1,2,3 around a circle would give 9 steps of resolution.

*/
#include <TouchWheel.h>

TouchWheel tw(A0, A1, A2);
boolean isTouching = false;

void setup() {
  Serial.begin(9600);
  tw.setFastAdc(); //hack the ADC to run 8x faster
  tw.calibrate(); //run this when no one is touching sensor
}

void loop() {
  int wheel = tw.scan();  //call this frequently and check the results
  if (wheel > 0) { //positive indicates one direction
    Serial.println("Wheel moved up!");
  } else if (wheel < 0) { //negative the other direction
    Serial.println("Wheel moved down!");
  }

  if (tw.isTouching() != isTouching) {
    isTouching = tw.isTouching();
    Serial.print("Wheel is touching: ");
    Serial.println(isTouching);
  }
}