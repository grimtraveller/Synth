#ifndef _SQUAREVOICE_H_
#define _SQUAREVOICE_H_

#include "JuceHeader.h"

class SquareVoice : public SynthesiserVoice {
public:
	SquareVoice()
		// WinkelDelta auf 0.0?
		// TailOff = sowas wie Release-Zeit?
		: angleDelta(0.0),
		tailOff(0.0)
	{}

	bool canPlaySound(SynthesiserSound* sound) override {
		//return dynamic_cast<SineSound*> (sound) != nullptr;
		return true;
	}

	void startNote(int midiNoteNumber, float velocity,
		SynthesiserSound* /*sound*/,
		int /*currentPitchWheelPosition*/) override {

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
		// darf nicht gelöscht werden! (warum?)
		angleDelta = cyclesPerSample * 2.0 * double_Pi;
	}

	void stopNote(float /*velocity*/, bool allowTailOff) override {
		clearCurrentNote();
		angleDelta = 0.0;
		index = 0;
	}

	void pitchWheelMoved(int /*newValue*/) override {
		// can't be bothered implementing this for the demo!
	}

	void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override {
		// not interested in controllers in this case.
	}

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override {
		processBlock(outputBuffer, startSample, numSamples);
	}

	void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override {
		processBlock(outputBuffer, startSample, numSamples);
	}

private:

	double cyclesPerSecond;
	double cyclesPerSample;
	float period;

	template <typename FloatType>
	void processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples) {

		// was passiert bei angleDelta == 0.0 ? (Knacken)
		// muss abgefragt werden! (warum?)
		if (angleDelta != 0.0) {

			// für jeden Sample:
			while (--numSamples >= 0) {

				//FloatType currentSample = 0.0;

				FloatType currentSample = static_cast<FloatType> (std::sin(2 * double_Pi * index * cyclesPerSecond / getSampleRate()));

				if (currentSample > 0) {
					currentSample = 1;
				}
				else {
					currentSample = 0;
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

	double currentAngle, angleDelta, level, tailOff;
	int index;
};

#endif//_SQUAREVOICE_H_