#ifndef touchwheel_h
#define touchwheel_h

#include "Arduino.h"
#include "AdcTouchChannel.h"

class TouchWheel {
public:
	TouchWheel(byte pin1, byte pin2, byte pin3) : c1(pin1), c2(pin2), c3(pin3) {};
	
	void calibrate() {
		c1.calibrate();
		c2.calibrate();
		c3.calibrate();
	}
	void setFastAdc() {
		AdcTouchChannel::setFastAdc();
	}

	int scan() {
		int res = 0;
		int value1 = c1.read();
		int value2 = c2.read();
		int value3 = c3.read();

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

	      if (value2 - value1 > delta) {
	        res = 1;
	        mode = 2;
	      } else if (value3 - value1 > delta) {
	        mode = 3;
	        res = -1;
	      } else if (value1 < lowThreshold) {
	        mode = 0;
	      }
	      break;
	    case 2:

	      if (value3 - value2 > delta) {
	        res = 1;
	        mode = 3;
	      } else if (value1 - value2 > delta) {
	        mode = 1;
	        res = -1;
	      } else if (value2 < lowThreshold) {
	        mode = 0;
	      }
	      break;
	    case 3:
	      if (value1 - value3 > delta) {
	        res = 1;
	        mode = 1;
	      } else if (value2 - value3 > delta) {
	        mode = 2;
	        res = -1;
	      } else if (value3 < lowThreshold) {
	        mode = 0;
	      }
	      break;
		}
		return res;
	}

	boolean TouchWheel::isTouching() {
		return mode != 0;
	}

private:
	AdcTouchChannel c1, c2, c3;
	int threshold = 25;
  	int lowThreshold = 12;
  	int delta = 5;
  	int mode = 0;
};


#endif
