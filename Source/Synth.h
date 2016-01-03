#ifndef _SYNTH_H_
#define _SYNTH_H_

#include "JuceHeader.h"
#include "vector"
#include "SynthVoice.h"

class Synth : public Synthesiser {
public:
	Synth() : Synthesiser() {
		waveForm = -1;
	}
	int getWaveForm() {
		return waveForm;
	}
	void setWaveForm(int waveForm) {
		this->waveForm = waveForm;
		for (int i = 0; i < voices.size(); i++) {
			SynthVoice* voice = dynamic_cast<SynthVoice*>(voices[i]);
			voice->setWaveForm(waveForm);
		}
	}
private:
	int waveForm;
};

#endif//_SYNTH_H_