/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/

#define SAMPLE_RATE   (44100)

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

class Add_synthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Add_synthAudioProcessor();
    ~Add_synthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    void setGainMIDI(float val);
    void setGain1(float val);
    void setFreq1(float val);
    void setGain2(float val);
    void setFreq2(float val);
    void setGain3(float val);
    void setFreq3(float val);
    
private:
    //==============================================================================
    
    float phaseMIDI;
    float phase1;
    float phase2;
    float phase3;
    
    float gainMIDI;
    float gainMIDINow;
    float gain1;
    float gainNow1;
    float gain2;
    float gainNow2;
    float gain3;
    float gainNow3;
    
    float car_freq;
    
    float freq1;
    float freq2;
    float freq3;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Add_synthAudioProcessor)
};
