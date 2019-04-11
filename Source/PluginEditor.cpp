/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//Label==============================================================================
Barton_a3AudioProcessorEditor::Barton_a3AudioProcessorEditor (Barton_a3AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setOpaque(true);

   //etSize (400, 300);
	setResizeLimits(300, 300, 1280, 1080);
	setResizable(true, true);

	//MixSlider=======================================================================
	mixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 12);
	mixSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aliceblue);
	mixSlider.addListener(this);
	mixSlider.setRange(0, 100.0f);
	mixSlider.setTextValueSuffix("%");
	addAndMakeVisible(mixSlider);

	addAndMakeVisible(mixLabel);
	addAndMakeVisible(mixSlider);
	mixLabel.setText("wet/Dry Mix", dontSendNotification);
	mixLabel.attachToComponent(&mixSlider, false);

	//effectSlider==================================================================
	effectSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	effectSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, false, 80, 12);
	effectSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::azure);
	effectSlider.addListener(this);
	effectSlider.setRange(4, 16);
	effectSlider.setTextValueSuffix("Power");
	effectSlider.setNumDecimalPlacesToDisplay(0);

	addAndMakeVisible(effectSlider);
	addAndMakeVisible(effectLabel);
	effectLabel.setText("Quantum Power", dontSendNotification);
	effectLabel.attachToComponent(&effectSlider, false);

}


Barton_a3AudioProcessorEditor::~Barton_a3AudioProcessorEditor()
{
}

//==============================================================================
void Barton_a3AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	g.setColour(Colours::azure);
    g.setFont (15.0f);
    g.drawFittedText ("Hello Matt", getLocalBounds(), Justification::centred, 1);
}

void Barton_a3AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto r = getLocalBounds();

	auto topSection = r.removeFromTop(100);
	auto bottomSection = r;
	mixSlider.setBounds(topSection);

	effectSlider.setBounds(bottomSection);
}
