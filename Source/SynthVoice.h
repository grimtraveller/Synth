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
		angleDelta = 0.0;
		tailOff = 0.0;
		currentState = OFF;
		gain = 0.0;
		waveForm = 0;
		attackMS = 0.0;
		decayMS = 0.0;
		sustainLevel = 1.0;
		releaseMS = 0.0;
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
		//gain = 0;
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

	int* getAttackMS() {
		return &attackMS;
	}

	void setAttackMS(int attackMS) {
		this->attackMS = attackMS;
	}

	int* getDecayMS() {
		return &decayMS;
	}

	void setDecayMS(int decayMS) {
		this->decayMS = decayMS;
	}

	int* getReleaseMS() {
		return &releaseMS;
	}

	void setReleaseMS(int releaseMS) {
		this->releaseMS = releaseMS;
	}

	float* getSustainLevel() {
		return &sustainLevel;
	}

	void setSustainLevel(float sustainLevel) {
		this->sustainLevel = sustainLevel;
	}

	void attack() {
		if (attackMS == 0) {
			if (sustainLevel > 0) {
				if (decayMS > 0) {
					gain = 1.0;
					currentState = DECAY;
				}
				else {
					currentState = SUSTAIN;
				}
			}
			else {
				gain = 1.0;
				currentState = RELEASE;
			}
		}
		else {
			// samples = ms * samplerate(48,0)
			int attackSamples = attackMS * 48;
			// gain-plus per sample:
			float gainDelta = 1.0 / attackSamples;
			// apply gain from first to last buffer sample:
			if (gain < 1.0) {
				gain = gain + gainDelta;
			}
			else if (gain >= 1.0) {
				gain = 1.0;
				currentState = DECAY;
			}
		}
	}

	void decay() {
		if (decayMS == 0) {
			if (sustainLevel == 0) {
				gain = 1.0;
				currentState = RELEASE;
			}
			else {
				gain = sustainLevel;
				currentState = SUSTAIN;
			}
		}
		else {
			// samples = ms * samplerate(48,0)
			int decaySamples = decayMS * 48;
			// gain-minus per sample:
			float gainDelta = (1.0 - sustainLevel) / decaySamples;
			// apply gain from first to last buffer sample:
			if (gain > sustainLevel) {
				gain = gain - gainDelta;
			}
			else if (gain <= sustainLevel) {
				gain = sustainLevel;
				currentState = SUSTAIN;
			}
		}
	}

	void sustain() {
		if (sustainLevel == 0) {
			gain = 1.0;
			currentState = RELEASE;
		}
		else {
			gain = sustainLevel;
		}
	}

	void release() {
		float currentGain;
		if (releaseMS == 0) {
			currentState = OFF;
		}
		else {
			if (sustainLevel == 0) {
				currentGain = 1.0;
			}
			else {
				currentGain = sustainLevel;
			}
			// samples = ms * samplerate(48,0)
			int releaseSamples = releaseMS * 48;
			// gain-minus per sample:
			float gainDelta = currentGain / releaseSamples;
			// apply gain from first to last buffer sample:
			if (gain > 0) {
				gain = gain - gainDelta;
			}
			if (gain <= 0) {
				gain = 0.0;
				currentState = OFF;
			}
		}
	}

private:

	double cyclesPerSecond, cyclesPerSample;
	double currentAngle, angleDelta, level, tailOff;
	float period, modulo, gain;
	int index, waveForm;
	state currentState;
	// Envelope:
	int attackMS, decayMS, releaseMS;
	float sustainLevel;
	//

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

				// Envelope:
				if (currentState == NOTEON) {
					currentState = ATTACK;
				}
				if (currentState == ATTACK) {
					attack();
				}
				if (currentState == DECAY) {
					decay();
				}
				if (currentState == SUSTAIN) {
					sustain();
				}
				if (currentState == NOTEOFF) {
					if (releaseMS > 0) {
						currentState = RELEASE;
					}
					else {
						currentState = OFF;
					}
				}
				if (currentState == RELEASE) {
					release();
				}
				if (currentState == OFF) {
					tailOff *= 0.99;
					gain = gain * tailOff;
					if (tailOff <= 0.005) {
						clearCurrentNote();
						gain = 0.0;
					}
				}

				// für jeden Channel:
				for (int i = outputBuffer.getNumChannels(); --i >= 0;) {
					// aktuellen Sample zum Buffer hinzufügen:
					outputBuffer.addSample(i, startSample, currentSample * gain);
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