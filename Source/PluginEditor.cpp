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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
	startTimer(200);//starts timer with interval of 200mS
    //[/Constructor_pre]

    addAndMakeVisible (waveformCombo = new ComboBox ("waveformCombo"));
    waveformCombo->setEditableText (false);
    waveformCombo->setJustificationType (Justification::centredLeft);
    waveformCombo->setTextWhenNothingSelected (TRANS("select waveform"));
    waveformCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    waveformCombo->addItem (TRANS("Sine"), 1);
    waveformCombo->addItem (TRANS("Triangle"), 2);
    waveformCombo->addItem (TRANS("Rectangle"), 3);
    waveformCombo->addItem (TRANS("Sawtooth"), 4);
    waveformCombo->addListener (this);

    addAndMakeVisible (console = new TextConsole());
    console->setName ("component");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..
	console->addListener(this);
    //[/Constructor]
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    waveformCombo = nullptr;
    console = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SynthAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff39bd9f));

    g.setColour (Colours::black);
    g.drawRect (0, 0, 200, 200, 1);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SynthAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    waveformCombo->setBounds (24, 16, 150, 24);
    console->setBounds (8, 56, 184, 136);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SynthAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
	SynthAudioProcessor* ourProcessor = getProcessor();
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == waveformCombo)
    {
        //[UserComboBoxCode_waveformCombo] -- add your combo box handling code here..
		ourProcessor->setParameter(1, waveformCombo->getSelectedItemIndex());
        //[/UserComboBoxCode_waveformCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SynthAudioProcessorEditor::timerCallback()
{
	SynthAudioProcessor* ourProcessor = getProcessor();
	//exchange any data you want between UI elements and the Plugin "ourProcessor"
	if (ourProcessor->consoleChanged == true) {
		console->addLine(ourProcessor->consoleText);
		ourProcessor->consoleChanged = false;
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SynthAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer, public TextEditorListener"
                 constructorParams="SynthAudioProcessor&amp; ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="ff39bd9f">
    <RECT pos="0 0 200 200" fill="solid: ffffff" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ff000000"/>
  </BACKGROUND>
  <COMBOBOX name="waveformCombo" id="fbac7f8dd6c0ec9b" memberName="waveformCombo"
            virtualName="" explicitFocusOrder="0" pos="24 16 150 24" editable="0"
            layout="33" items="Sine&#10;Triangle&#10;Rectangle&#10;Sawtooth"
            textWhenNonSelected="select waveform" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="component" id="4276f77e827d2135" memberName="console" virtualName=""
                    explicitFocusOrder="0" pos="8 56 184 136" class="TextConsole"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
