
#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include "JuceHeader.h"
#include <vector>

class RingBuffer : AudioSampleBuffer {
public:
	RingBuffer();
	void write(float sample);
	float readWithDelay(int delay);
	void resize(int size);
	int getSize();
private:
	std::vector<float> buffer;
	int writeIndex;
	int size;
};

#endif//_RINGBUFFER_H_