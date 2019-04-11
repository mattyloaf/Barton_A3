/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Barton_a3AudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener 
{
public:
    Barton_a3AudioProcessorEditor (Barton_a3AudioProcessor&);
    ~Barton_a3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider * slider) override
	{
		if (slider == &mixSlider) {
			processor.mixLevel = mixSlider.getValue();
		}
		else if (slider == &effectSlider)
		{
			processor.power = effectSlider.getValue();
		}
	}


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

	Slider mixSlider;
	Label mixLabel;

	Slider freqSlider;
	Label freqLabel;

	Slider  effectSlider;
	Label effectLabel;

	

    Barton_a3AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Barton_a3AudioProcessorEditor)
};
