/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.0.2

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_FB6CB5DF34E360D__
#define __JUCE_HEADER_FB6CB5DF34E360D__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "TextConsole.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SynthAudioProcessorEditor  : public AudioProcessorEditor,
                                   public Timer,
                                   public TextEditorListener,
                                   public ComboBoxListener,
                                   public SliderListener
{
public:
    //==============================================================================
    SynthAudioProcessorEditor (SynthAudioProcessor& ownerFilter);
    ~SynthAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	void timerCallback();

	SynthAudioProcessor* getProcessor() const
	{
		return static_cast <SynthAudioProcessor*>(getAudioProcessor());
	}

	//void textChanged(TextConsole* consoleThatHasChanged);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* synthKopie_jpg;
    static const int synthKopie_jpgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> waveformCombo;
    ScopedPointer<TextConsole> console;
    ScopedPointer<Slider> attackSlider;
    ScopedPointer<Slider> delayLengthSlider;
    ScopedPointer<Slider> dryMixSlider;
    ScopedPointer<Slider> wetMixSlider;
    ScopedPointer<Slider> decaySlider;
    ScopedPointer<Slider> sustainSlider;
    ScopedPointer<Slider> releaseSlider;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> label8;
    ScopedPointer<Slider> noiseSlider;
    ScopedPointer<Label> label9;
    Image cachedImage_synthKopie_jpg_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_FB6CB5DF34E360D__
