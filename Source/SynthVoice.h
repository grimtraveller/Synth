#ifndef _SYNTHVOICE_H_
#define _SYNTHVOICE_H_

#include "JuceHeader.h"

class SynthVoice : public SynthesiserVoice {
public:
	SynthVoice() : SynthesiserVoice() {
		// WinkelDelta auf 0.0?
		// TailOff = sowas wie Release-Zeit?
		angleDelta = 0.0;
		tailOff = 0.0;
		state = OFF;
	}

	bool canPlaySound(SynthesiserSound* sound) override {
		//return dynamic_cast<SineSound*> (sound) != nullptr;
		return true;
	}

	void startNote(int midiNoteNumber, float velocity,
		SynthesiserSound* /*sound*/,
		int /*currentPitchWheelPosition*/) override {

		state = NOTEON;

		// entfernen verursacht Knacken:
		currentAngle = 0.0;
		level = velocity * 0.15;
		tailOff = 0.0;
		index = 0;

		// Cycles per second = Frequenz in Hertz
		// Cycle = ein Sinuswellendurchgang (= 2 x Pi)
		// Winkelfrequenz = 2 Pi * Frequenz!
		cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

		// Cycles per sample = Frequenz / SampleRate
		cyclesPerSample = cyclesPerSecond / getSampleRate();

		period = getSampleRate() / cyclesPerSecond;

		// value = 2 * Pi * index * frequency/samplerate
		// darf nicht gel�scht werden! (warum?)
		angleDelta = cyclesPerSample * 2.0 * double_Pi;
	}

	void stopNote(float /*velocity*/, bool allowTailOff) override {
		//clearCurrentNote();
		//angleDelta = 0.0;
		//index = 0;
		state = NOTEOFF;
	}

	void pitchWheelMoved(int /*newValue*/) override {
		// can't be bothered implementing this for the demo!
	}

	void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override {
		// not interested in controllers in this case.
	}

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override {
		if (state == OFF) {
			clearCurrentNote();
		}
		else {
			processBlock(outputBuffer, startSample, numSamples);
		}
	}

	void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override {
		if (state == OFF) {
			clearCurrentNote();
		}
		else {
			processBlock(outputBuffer, startSample, numSamples);
		}
	}

	enum state {
		ON,
		NOTEON,
		NOTEOFF,
		OFF
	};
	state state;

	bool isSynthVoiceActive() {
		if (getCurrentlyPlayingNote() >= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	std::string getState() {
		if (state == NOTEON) {
			return "NOTEON";
		}
		else if (state == NOTEOFF) {
			return "NOTEOFF";
		}
		else {
			return "OFF";
		}
	}

	void setState(enum SynthVoice::state s) {
		state = s;
	}

	int index;

private:

	double cyclesPerSecond;
	double cyclesPerSample;
	float period;

	template <typename FloatType>
	void processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples) {
		
		// was passiert bei angleDelta == 0.0 ? (Knacken)
		// muss abgefragt werden! (warum?)
		if (angleDelta != 0.0) {

			// f�r jeden Sample:
			while (--numSamples >= 0) {
				// aktueller Winkel + WinkelDelta: (ein Schritt weiter im Sinus?)
				//currentAngle += angleDelta;
				// ein Schritt weiter im Sample?
				++startSample;
				index++;
			}

		}// if(angleDelta != 0.0)

	}// void processsBlock()

	double currentAngle, angleDelta, level, tailOff;
};

#endif//_SYNTHVOICE_H_