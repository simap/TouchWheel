#ifndef adctouchchannel_h
#define adctouchchannel_h

class AdcTouchChannel {
public:
	AdcTouchChannel(byte channel, int samples = 8) : channel(channel), samples(samples) {
		// calibrate();
	};
	void calibrate() {
		calibration = read();
	};
	int read() {
		long total = 0;
		for (int i = 0; i < samples; i ++) {
			pinMode(channel, INPUT_PULLUP);
			
			ADMUX |=   0b11111;
			ADCSRA |= (1<<ADSC); //start conversion
			while(!(ADCSRA & (1<<ADIF))); //wait for conversion to finish
			ADCSRA |= (1<<ADIF); //reset the flag
			
			pinMode(channel, INPUT);
			total += analogRead(channel);
		}
		return max(0, total / samples - calibration);
	};

	static void setFastAdc() {
		const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
		const unsigned char PS_16 = (1 << ADPS2);
		ADCSRA &= ~PS_128;  // remove bits set by Arduino library
		ADCSRA |= PS_16;
	};

private:
	int calibration;
	byte channel;
	int samples;
};

#endif adctouchchannel_h
