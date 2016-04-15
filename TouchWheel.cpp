/*
TouchWheel. Needs ADCTouch
*/

#include <ADCTouch.h>
#include "TouchWheel.h"

void TouchWheel::calibrate() {
	cal1 = ADCTouch.read(pin1, 500);
	cal2 = ADCTouch.read(pin2, 500);
	cal3 = ADCTouch.read(pin3, 500);
}

void TouchWheel::setFastAdc() {
	const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	const unsigned char PS_16 = (1 << ADPS2);
	ADCSRA &= ~PS_128;  // remove bits set by Arduino library
	ADCSRA |= PS_16;
}

int TouchWheel::scan() {
	int res = 0;
	int value1 = ADCTouch.read(pin1, 8);
	int value2 = ADCTouch.read(pin2, 8);
	int value3 = ADCTouch.read(pin3, 8);
	value1 -= cal1;
	value2 -= cal2;
	value3 -= cal3;

	switch (mode) {
    case 0:
      if (value1 > threshold)
        mode = 1;
      else if (value2 > threshold)
        mode = 2;
      else if (value3 > threshold)
        mode = 3;
      break;
    case 1:

      if (value2 - value1 > lowThreshold) {
        res = 1;
        mode = 2;
      } else if (value3 - value1 > lowThreshold) {
        mode = 3;
        res = -1;
      } else if (value1 < lowThreshold) {
        mode = 0;
      }
      break;
    case 2:

      if (value3 - value2 > lowThreshold) {
        res = 1;
        mode = 3;
      } else if (value1 - value2 > lowThreshold) {
        mode = 1;
        res = -1;
      } else if (value2 < lowThreshold) {
        mode = 0;
      }
      break;
    case 3:
      if (value1 - value3 > lowThreshold) {
        res = 1;
        mode = 1;
      } else if (value2 - value3 > lowThreshold) {
        mode = 2;
        res = -1;
      } else if (value3 < lowThreshold) {
        mode = 0;
      }
      break;
	}
	return res;
}