/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Add_synthAudioProcessor::Add_synthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Add_synthAudioProcessor::~Add_synthAudioProcessor()
{
}

//==============================================================================
const juce::String Add_synthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Add_synthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Add_synthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Add_synthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Add_synthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Add_synthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Add_synthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Add_synthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Add_synthAudioProcessor::getProgramName (int index)
{
    return {};
}

void Add_synthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Add_synthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    gainMIDI = 0; 
    gainMIDINow = 0;
    gain1 = 0;
    gain2 = 0;
    gain3 = 0;
    gainNow1 = 0;
    gainNow2 = 0;
    gainNow3 = 0;
    phaseMIDI = 0.0;
    phase1 = 0.0;
    phase2 = 0.0;
    phase3 = 0.0;
    car_freq = 0.0;
    freq1 = 1.0;
    freq2 = 0.0;
    freq3 = 0.0;
    
}

void Add_synthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Add_synthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void Add_synthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
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
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    float mod;
    juce::MidiMessage m;
    int time;
    for (juce::MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);){
        if (m.isNoteOn()) {
            gainMIDINow = gainMIDI;
            gainNow1 = gain1;
            gainNow2 = gain2;
            gainNow3 = gain3;
            car_freq = m.getMidiNoteInHertz(m.getNoteNumber());
        }
        else if (m.isNoteOff()) {
            gainMIDINow = 0;
            gainNow1 = 0;
            gainNow2 = 0;
            gainNow3 = 0;
        }
        else if (m.isAftertouch()) {
        }
        else if (m.isPitchWheel()) {
        }
    }
    
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);
    int numSamples = buffer.getNumSamples();
    float sinMIDI;
    float sin1;
    float sin2;
    float sin3;
    
    for (int i = 0; i < numSamples; ++i) {
        sinMIDI = gainMIDINow * (float) sin ((double) phaseMIDI);
        sin1 = gainNow1 * (float) sin ((double) phase1);
        sin2 = gainNow2 * (float) sin ((double) phase2);
        sin3 = gainNow3 * (float) sin ((double) phase3);
        channelDataL[i] = sinMIDI + sin1 + sin2 + sin3;
        channelDataR[i] = channelDataL[i];
        
        
        
        phaseMIDI += (float) ( M_PI * 2. *( ((double) (car_freq) / (double) SAMPLE_RATE)));
        if( phaseMIDI > M_PI * 2. ) phaseMIDI -= M_PI * 2.;
        phase1 += (float) ( M_PI * 2. *( ((double) (car_freq*(pow (2.0, freq1))) / (double) SAMPLE_RATE)));
        if( phase1 > M_PI * 2. ) phase1 -= M_PI * 2.;
        phase2 += (float) ( M_PI * 2. *( ((double) (car_freq*(pow (2.0, freq2))) / (double) SAMPLE_RATE)));
        if( phase2 > M_PI * 2. ) phase2 -= M_PI * 2.;
        phase3 += (float) ( M_PI * 2. *( ((double) (car_freq*(pow (2.0, freq3))) / (double) SAMPLE_RATE)));
        if( phase3 > M_PI * 2. ) phase3 -= M_PI * 2.;
        
    }
    
}

//==============================================================================
bool Add_synthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Add_synthAudioProcessor::createEditor()
{
    return new Add_synthAudioProcessorEditor (*this);
}

//==============================================================================
void Add_synthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Add_synthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Add_synthAudioProcessor();
}



void Add_synthAudioProcessor::setGainMIDI(float val)
{
    gainMIDI = val;
}

void Add_synthAudioProcessor::setGain1(float val)
{
    gain1 = val;
}

void Add_synthAudioProcessor::setFreq1(float val)
{
    freq1 = val;
}

void Add_synthAudioProcessor::setGain2(float val)
{
    gain2 = val;
}

void Add_synthAudioProcessor::setFreq2(float val)
{
    freq2 = val;
}

void Add_synthAudioProcessor::setGain3(float val)
{
    gain3 = val;
}

void Add_synthAudioProcessor::setFreq3(float val)
{
    freq3 = val;
}

