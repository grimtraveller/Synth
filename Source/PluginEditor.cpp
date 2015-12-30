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
	startTimer(50);//starts timer (ms)
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

    addAndMakeVisible (attackSlider = new Slider ("attackSlider"));
    attackSlider->setRange (0, 3000, 10);
    attackSlider->setSliderStyle (Slider::LinearHorizontal);
    attackSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    attackSlider->addListener (this);

    addAndMakeVisible (delayLengthSlider = new Slider ("delayLengthSlider"));
    delayLengthSlider->setRange (0, 1000, 10);
    delayLengthSlider->setSliderStyle (Slider::LinearHorizontal);
    delayLengthSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    delayLengthSlider->addListener (this);

    addAndMakeVisible (waveFormLabel = new Label ("waveFormLabel",
                                                  TRANS("Wave Form:")));
    waveFormLabel->setFont (Font (15.00f, Font::plain));
    waveFormLabel->setJustificationType (Justification::centredLeft);
    waveFormLabel->setEditable (false, false, false);
    waveFormLabel->setColour (TextEditor::textColourId, Colours::black);
    waveFormLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackLabel = new Label ("attackLabel",
                                                TRANS("Attack (ms):")));
    attackLabel->setFont (Font (15.00f, Font::plain));
    attackLabel->setJustificationType (Justification::centredLeft);
    attackLabel->setEditable (false, false, false);
    attackLabel->setColour (TextEditor::textColourId, Colours::black);
    attackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayLengthLabel = new Label ("delayLengthLabel",
                                                     TRANS("Delay Length (ms):")));
    delayLengthLabel->setFont (Font (15.00f, Font::plain));
    delayLengthLabel->setJustificationType (Justification::centredLeft);
    delayLengthLabel->setEditable (false, false, false);
    delayLengthLabel->setColour (TextEditor::textColourId, Colours::black);
    delayLengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dryMixSlider = new Slider ("dryMixSlider"));
    dryMixSlider->setRange (0, 100, 10);
    dryMixSlider->setSliderStyle (Slider::LinearHorizontal);
    dryMixSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    dryMixSlider->addListener (this);

    addAndMakeVisible (wetMixSlider = new Slider ("wetMixSlider"));
    wetMixSlider->setRange (0, 100, 10);
    wetMixSlider->setSliderStyle (Slider::LinearHorizontal);
    wetMixSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    wetMixSlider->addListener (this);

    addAndMakeVisible (dryMixLabel = new Label ("dryMixLabel",
                                                TRANS("Dry Mix (%):")));
    dryMixLabel->setFont (Font (15.00f, Font::plain));
    dryMixLabel->setJustificationType (Justification::centredLeft);
    dryMixLabel->setEditable (false, false, false);
    dryMixLabel->setColour (TextEditor::textColourId, Colours::black);
    dryMixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wetMixLabel = new Label ("wetMixLabel",
                                                TRANS("Wet Mix (%):")));
    wetMixLabel->setFont (Font (15.00f, Font::plain));
    wetMixLabel->setJustificationType (Justification::centredLeft);
    wetMixLabel->setEditable (false, false, false);
    wetMixLabel->setColour (TextEditor::textColourId, Colours::black);
    wetMixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (decaySlider = new Slider ("decaySlider"));
    decaySlider->setRange (0, 3000, 10);
    decaySlider->setSliderStyle (Slider::LinearHorizontal);
    decaySlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    decaySlider->addListener (this);

    addAndMakeVisible (decayLabel = new Label ("decayLabel",
                                               TRANS("Decay (ms):")));
    decayLabel->setFont (Font (15.00f, Font::plain));
    decayLabel->setJustificationType (Justification::centredLeft);
    decayLabel->setEditable (false, false, false);
    decayLabel->setColour (TextEditor::textColourId, Colours::black);
    decayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustainSlider = new Slider ("sustainSlider"));
    sustainSlider->setRange (0, 100, 10);
    sustainSlider->setSliderStyle (Slider::LinearHorizontal);
    sustainSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sustainSlider->addListener (this);

    addAndMakeVisible (sustainLabel = new Label ("sustainLabel",
                                                 TRANS("Sustain (gain):")));
    sustainLabel->setFont (Font (15.00f, Font::plain));
    sustainLabel->setJustificationType (Justification::centredLeft);
    sustainLabel->setEditable (false, false, false);
    sustainLabel->setColour (TextEditor::textColourId, Colours::black);
    sustainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseSlider = new Slider ("releaseSlider"));
    releaseSlider->setRange (0, 3000, 10);
    releaseSlider->setSliderStyle (Slider::LinearHorizontal);
    releaseSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    releaseSlider->addListener (this);

    addAndMakeVisible (releaseLabel = new Label ("releaseLabel",
                                                 TRANS("Release (ms):")));
    releaseLabel->setFont (Font (15.00f, Font::plain));
    releaseLabel->setJustificationType (Justification::centredLeft);
    releaseLabel->setEditable (false, false, false);
    releaseLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 500);


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
    attackSlider = nullptr;
    delayLengthSlider = nullptr;
    waveFormLabel = nullptr;
    attackLabel = nullptr;
    delayLengthLabel = nullptr;
    dryMixSlider = nullptr;
    wetMixSlider = nullptr;
    dryMixLabel = nullptr;
    wetMixLabel = nullptr;
    decaySlider = nullptr;
    decayLabel = nullptr;
    sustainSlider = nullptr;
    sustainLabel = nullptr;
    releaseSlider = nullptr;
    releaseLabel = nullptr;


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
    g.drawRect (0, 0, 400, 500, 1);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SynthAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    waveformCombo->setBounds (160, 16, 176, 24);
    console->setBounds (8, 256, 384, 236);
    attackSlider->setBounds (160, 48, 176, 24);
    delayLengthSlider->setBounds (160, 152, 176, 24);
    waveFormLabel->setBounds (16, 16, 150, 24);
    attackLabel->setBounds (16, 48, 150, 24);
    delayLengthLabel->setBounds (16, 152, 150, 24);
    dryMixSlider->setBounds (160, 184, 176, 24);
    wetMixSlider->setBounds (160, 216, 176, 24);
    dryMixLabel->setBounds (16, 184, 150, 24);
    wetMixLabel->setBounds (16, 216, 150, 24);
    decaySlider->setBounds (160, 74, 176, 24);
    decayLabel->setBounds (16, 74, 150, 24);
    sustainSlider->setBounds (160, 99, 176, 24);
    sustainLabel->setBounds (16, 99, 150, 24);
    releaseSlider->setBounds (160, 125, 176, 24);
    releaseLabel->setBounds (16, 125, 150, 24);
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

void SynthAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	SynthAudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attackSlider)
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
		ourProcessor->setParameter(2, attackSlider->getValue());
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == delayLengthSlider)
    {
        //[UserSliderCode_delayLengthSlider] -- add your slider handling code here..
		ourProcessor->setParameter(3, delayLengthSlider->getValue());
		ourProcessor->ringBuffer.resize(ourProcessor->delayLengthMS * 48);
        //[/UserSliderCode_delayLengthSlider]
    }
    else if (sliderThatWasMoved == dryMixSlider)
    {
        //[UserSliderCode_dryMixSlider] -- add your slider handling code here..
		ourProcessor->setParameter(4, dryMixSlider->getValue());
        //[/UserSliderCode_dryMixSlider]
    }
    else if (sliderThatWasMoved == wetMixSlider)
    {
        //[UserSliderCode_wetMixSlider] -- add your slider handling code here..
		ourProcessor->setParameter(5, wetMixSlider->getValue());
        //[/UserSliderCode_wetMixSlider]
    }
    else if (sliderThatWasMoved == decaySlider)
    {
        //[UserSliderCode_decaySlider] -- add your slider handling code here..
		ourProcessor->setParameter(6, decaySlider->getValue());
        //[/UserSliderCode_decaySlider]
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
        //[UserSliderCode_sustainSlider] -- add your slider handling code here..
		ourProcessor->setParameter(7, sustainSlider->getValue());
        //[/UserSliderCode_sustainSlider]
    }
    else if (sliderThatWasMoved == releaseSlider)
    {
        //[UserSliderCode_releaseSlider] -- add your slider handling code here..
		ourProcessor->setParameter(8, releaseSlider->getValue());
        //[/UserSliderCode_releaseSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SynthAudioProcessorEditor::timerCallback()
{
	SynthAudioProcessor* ourProcessor = getProcessor();
	// console:
	if (ourProcessor->consoleChanged == true) {
		console->addLine(ourProcessor->consoleText);
		ourProcessor->consoleChanged = false;
	}
	// envelope slider:
	waveformCombo->setSelectedItemIndex(ourProcessor->waveForm);
	attackSlider->setValue(ourProcessor->attackMS);
	decaySlider->setValue(ourProcessor->decayMS);
	sustainSlider->setValue(ourProcessor->sustain);
	releaseSlider->setValue(ourProcessor->releaseMS);
	// delay slider:
	delayLengthSlider->setValue(ourProcessor->delayLengthMS);
	dryMixSlider->setValue(ourProcessor->dryMix);
	wetMixSlider->setValue(ourProcessor->wetMix);
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
                 fixedSize="1" initialWidth="400" initialHeight="500">
  <BACKGROUND backgroundColour="ff39bd9f">
    <RECT pos="0 0 400 500" fill="solid: ffffff" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ff000000"/>
  </BACKGROUND>
  <COMBOBOX name="waveformCombo" id="fbac7f8dd6c0ec9b" memberName="waveformCombo"
            virtualName="" explicitFocusOrder="0" pos="160 16 176 24" editable="0"
            layout="33" items="Sine&#10;Triangle&#10;Rectangle&#10;Sawtooth"
            textWhenNonSelected="select waveform" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="component" id="4276f77e827d2135" memberName="console" virtualName=""
                    explicitFocusOrder="0" pos="8 256 384 236" class="TextConsole"
                    params=""/>
  <SLIDER name="attackSlider" id="a83899bf58c16d70" memberName="attackSlider"
          virtualName="" explicitFocusOrder="0" pos="160 48 176 24" min="0"
          max="3000" int="10" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="delayLengthSlider" id="5bbd6216e7358767" memberName="delayLengthSlider"
          virtualName="" explicitFocusOrder="0" pos="160 152 176 24" min="0"
          max="1000" int="10" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="waveFormLabel" id="160034d69ab41d94" memberName="waveFormLabel"
         virtualName="" explicitFocusOrder="0" pos="16 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Wave Form:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="attackLabel" id="7a473bac9ca0eeae" memberName="attackLabel"
         virtualName="" explicitFocusOrder="0" pos="16 48 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack (ms):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="delayLengthLabel" id="f6594004d354d5bd" memberName="delayLengthLabel"
         virtualName="" explicitFocusOrder="0" pos="16 152 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay Length (ms):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="dryMixSlider" id="8f362ceecad426d5" memberName="dryMixSlider"
          virtualName="" explicitFocusOrder="0" pos="160 184 176 24" min="0"
          max="100" int="10" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="wetMixSlider" id="4a20f9eb94bdfeeb" memberName="wetMixSlider"
          virtualName="" explicitFocusOrder="0" pos="160 216 176 24" min="0"
          max="100" int="10" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="dryMixLabel" id="c653c7ea1937ccb2" memberName="dryMixLabel"
         virtualName="" explicitFocusOrder="0" pos="16 184 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Dry Mix (%):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="wetMixLabel" id="e64569e6a4375103" memberName="wetMixLabel"
         virtualName="" explicitFocusOrder="0" pos="16 216 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Wet Mix (%):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="decaySlider" id="d450297afcba37a" memberName="decaySlider"
          virtualName="" explicitFocusOrder="0" pos="160 74 176 24" min="0"
          max="3000" int="10" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="decayLabel" id="5fab608d1006f0b3" memberName="decayLabel"
         virtualName="" explicitFocusOrder="0" pos="16 74 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Decay (ms):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="sustainSlider" id="77620e94b858d8b8" memberName="sustainSlider"
          virtualName="" explicitFocusOrder="0" pos="160 99 176 24" min="0"
          max="100" int="10" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="sustainLabel" id="7e55c8573a52366a" memberName="sustainLabel"
         virtualName="" explicitFocusOrder="0" pos="16 99 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sustain (gain):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="releaseSlider" id="fde925afa4de17f9" memberName="releaseSlider"
          virtualName="" explicitFocusOrder="0" pos="160 125 176 24" min="0"
          max="3000" int="10" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="releaseLabel" id="ab730d6e295f8301" memberName="releaseLabel"
         virtualName="" explicitFocusOrder="0" pos="16 125 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release (ms):" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
