#ifndef touchslider_h
#define touchslider_h

#include "Arduino.h"
#include "AdcTouchChannel.h"

class TouchSlider {
public:
	TouchSlider(byte pin1, byte pin2) : c1(pin1), c2(pin2) {};
	
	void calibrate() {
		c1.calibrate();
		c2.calibrate();
	}
	void setFastAdc() {
		AdcTouchChannel::setFastAdc();
	}
	float scan() {
		int res = 0;
		int value1 = c1.read();
		int value2 = c2.read();
	  
		res = value1+value2;
		if (res > threshold) {
			mode = 1;
			return value1 / (float) res;
		} else {
			mode = 0;
			return -1;
		}
	}
	boolean isTouching() {
		return mode != 0;
	}
private:
	AdcTouchChannel c1, c2;
	int threshold = 30;
	int mode = 0;
};

#endif





