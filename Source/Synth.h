#ifndef _SYNTH_H_
#define _SYNTH_H_

#include "JuceHeader.h"
#include "vector"
#include "SynthVoice.h"

class Synth : public Synthesiser {
public:
	Synth() : Synthesiser() {

	}

	void addSynthVoice(SynthVoice* synthVoice) {
		voices.push_back(synthVoice);
	}

	std::vector<SynthVoice*>* getSynthVoices() {
		return &voices;
	}

	SynthVoice* getSynthVoice(int index) {
		return voices.at(index);
	}

private:
	std::vector<SynthVoice*> voices;
};

#endif//_SYNTH_H_