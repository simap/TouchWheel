#ifndef touchwheel_h
#define touchwheel_h

#include "Arduino.h"



class TouchWheel {
public:
	TouchWheel(int pin1, int pin2, int pin3) : pin1(pin1), pin2(pin2), pin3(pin3) {};
	void calibrate();
	void setFastAdc();
	int scan();
	boolean isTouching();
private:
	int pin1, pin2, pin3;
	int cal1, cal2, cal3;
	int threshold = 25;
  	int lowThreshold = 12;
  	int delta = 5;
  	int mode = 0;
};

#endif
