#ifndef _SYNTHVOICE_H_
#define _SYNTHVOICE_H_

#include "JuceHeader.h"

class SynthVoice : public SynthesiserVoice {
public:

	enum state {
		NOTEON,
		ATTACK,
		ON,
		DECAY,
		SUSTAIN,
		NOTEOFF,
		RELEASE,
		OFF
	};

	SynthVoice() : SynthesiserVoice() {
		// WinkelDelta auf 0.0?
		// TailOff = sowas wie Release-Zeit?
		angleDelta = 0.0;
		tailOff = 1.0;
		currentState = OFF;
		gain = 0.0;
		waveForm = -1;
	}

	bool canPlaySound(SynthesiserSound* sound) override {
		//return dynamic_cast<SineSound*> (sound) != nullptr;
		return true;
	}

	void startNote(int midiNoteNumber, float velocity,
		SynthesiserSound* /*sound*/,
		int /*currentPitchWheelPosition*/) override {

		currentState = NOTEON;

		// entfernen verursacht Knacken:
		currentAngle = 0.0;
		//level = velocity * 0.15;
		tailOff = 1.0;
		index = 0;
		gain = 0;

		// Cycles per second = Frequenz in Hertz
		// Cycle = ein Sinuswellendurchgang (= 2 x Pi)
		// Winkelfrequenz = 2 Pi * Frequenz!
		cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

		// Cycles per sample = Frequenz / SampleRate
		cyclesPerSample = cyclesPerSecond / getSampleRate();

		period = getSampleRate() / cyclesPerSecond;

		// value = 2 * Pi * index * frequency/samplerate
		// darf nicht gelöscht werden! (warum?)
		angleDelta = cyclesPerSample * 2.0 * double_Pi;
	}

	void stopNote(float /*velocity*/, bool allowTailOff) override {
		//clearCurrentNote();
		//angleDelta = 0.0;
		//index = 0;
		currentState = NOTEOFF;
	}

	void pitchWheelMoved(int /*newValue*/) override {
		// can't be bothered implementing this for the demo!
	}

	void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override {
		// not interested in controllers in this case.
	}

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override {
		if (currentState == OFF) {
			clearCurrentNote();
		}
		else {
			processBlock(outputBuffer, startSample, numSamples);
		}
	}

	void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override {
		if (currentState == OFF) {
			clearCurrentNote();
		}
		else {
			processBlock(outputBuffer, startSample, numSamples);
		}
	}

	int getWaveForm() {
		return waveForm;
	}

	void setWaveForm(int waveForm) {
		this->waveForm = waveForm;
	}

	state getState() {
		return currentState;
	}

	void setState(state currentState) {
		this->currentState = currentState;
	}

	float* getGain() {
		return &gain;
	}

	void setGain(float gain) {
		this->gain = gain;
	}

private:

	double cyclesPerSecond, cyclesPerSample;
	double currentAngle, angleDelta, level, tailOff;
	float period, modulo, gain;
	int index, waveForm;
	state currentState;

	template <typename FloatType>
	void processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples) {
		
		// was passiert bei angleDelta == 0.0 ? (Knacken)
		// muss abgefragt werden! (warum?)
		if (angleDelta != 0.0) {

			// für jeden Sample:
			while (--numSamples >= 0) {
				FloatType currentSample;
				if (waveForm == 0) {
					currentSample = static_cast<FloatType> (std::sin(2 * double_Pi * index * cyclesPerSecond / getSampleRate()));
				}
				else if (waveForm == 1) {
					float modulo = fmod(index, period);
					currentSample = static_cast<FloatType> ((modulo / period) * 4);
					if (currentSample < 2){
						currentSample = (currentSample - 1);
					}
					else{
						currentSample = (1 + 2 - currentSample);
					}
				}
				else if (waveForm == 2) {
					currentSample = static_cast<FloatType> (std::sin(2 * double_Pi * index * cyclesPerSecond / getSampleRate()));
					if (currentSample > 0) {
						currentSample = 1;
					}
					else {
						currentSample = 0;
					}
				}
				else if (waveForm == 3) {
					modulo = fmod(index, period);
					currentSample = static_cast<FloatType> ((modulo / period) * 2 - 1);
				}
				// für jeden Channel:
				for (int i = outputBuffer.getNumChannels(); --i >= 0;) {
					// aktuellen Sample zum Buffer hinzufügen:
					outputBuffer.addSample(i, startSample, currentSample);
				}
				// aktueller Winkel + WinkelDelta: (ein Schritt weiter im Sinus?)
				//currentAngle += angleDelta;
				// ein Schritt weiter im Sample?
				++startSample;
				index++;
			}

		}// if(angleDelta != 0.0)

	}// void processsBlock()

};

#endif//_SYNTHVOICE_H_