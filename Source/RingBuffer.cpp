
#include "RingBuffer.h"

RingBuffer::RingBuffer()
	: size(0), writeIndex(0)
{}

void RingBuffer::resize(int size){
	this->size = size;
	buffer.resize(size);
}

int RingBuffer::getSize() {
	return this->size;
}

void RingBuffer::write(float sample){
	if (writeIndex < buffer.size()) {
		buffer[writeIndex] = sample;
	}
	writeIndex++;
	if (writeIndex == size){
		writeIndex = 0;
	}
}

float RingBuffer::readWithDelay(int delay){
	int readIndex = writeIndex - delay;
	if (readIndex < 0){
		readIndex += size;
	}
	if (readIndex < buffer.size()) {
		return buffer[readIndex];
	}
	else {
		return buffer[0];
	}
}