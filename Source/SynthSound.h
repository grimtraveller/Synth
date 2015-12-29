#ifndef _SYNTHSOUND_H_
#define _SYNTHSOUND_H_

#include "JuceHeader.h"

class SynthSound : public SynthesiserSound {
public:
	SynthSound() {}
	bool appliesToNote(int /*midiNoteNumber*/) override  { return true; }
	bool appliesToChannel(int /*midiChannel*/) override  { return true; }
};

#endif//_SYNTHSOUND_H_