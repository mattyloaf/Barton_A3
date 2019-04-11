/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Barton_a3AudioProcessor::Barton_a3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	currentSampleRate = 0.0f;
	currentAngle = 0.0f;
	angleDelta = 0.0f;
	sinFreq = 60.0f;
}

Barton_a3AudioProcessor::~Barton_a3AudioProcessor()
{
}

//==============================================================================
const String Barton_a3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Barton_a3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Barton_a3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Barton_a3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Barton_a3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Barton_a3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Barton_a3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Barton_a3AudioProcessor::setCurrentProgram (int index)
{
}

const String Barton_a3AudioProcessor::getProgramName (int index)
{
    return {};
}

void Barton_a3AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Barton_a3AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) 
//id releaseResources() override;
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	currentSampleRate = sampleRate;
	sinFreq = 60.0f;
	updateAngleDelta();

	mixLevel = 0.15f;

	//in.setGainDecibels(0.0f);
	mixLevel.reset(sampleRate, 0.05f);
	mixLevel.setTargetValue(0.15f);
}

void Barton_a3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Barton_a3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Barton_a3AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
	

	AudioBuffer<float> wetBuffer(totalNumInputChannels, buffer.getNumSamples());
	wetBuffer.makeCopyOf(buffer);


	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);
		auto* wetData = wetBuffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{

			auto currentSinSample = (float)std::sin(currentAngle);
			currentAngle += angleDelta;


			wetData[sample] = wetData[sample] * currentSinSample;

			float quantum = powf(1.0f, power.getNextValue());

			auto shapedSample = floor(wetData[sample] * quantum) / quantum;
			wetData[sample] = shapedSample;

			channelData[sample] = channelData[sample] * mixLevel.getNextValue();

			// ..do something to the data...
		}
		//p::AudioBlock<float> output(buffer);
		//in.process(dsp::ProcessContextReplacing<float>(output));
	}
}

//==============================================================================
bool Barton_a3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Barton_a3AudioProcessor::createEditor()
{
    return new Barton_a3AudioProcessorEditor (*this);
}

//==============================================================================
void Barton_a3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Barton_a3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//===================================================================
//user functions
void Barton_a3AudioProcessor::updateAngleDelta()
{

	auto cyclesPerSample = sinFreq / currentSampleRate;

	angleDelta = cyclesPerSample * 2.0f * MathConstants<float>::twoPi;

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Barton_a3AudioProcessor();
}
