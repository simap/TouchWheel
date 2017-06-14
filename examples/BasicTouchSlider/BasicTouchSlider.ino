#include "TouchSlider.h"

TouchSlider ts(A0, A1);

void setup() {
  Serial.begin(9600);
  ts.setFastAdc();
  ts.calibrate();
}

void loop() {
  Serial.println(ts.scan());
  delay(500);
}
