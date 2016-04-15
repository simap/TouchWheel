#include <TouchWheel.h>

TouchWheel tw(A0, A1, A2);

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
}