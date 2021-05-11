/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Add_synthAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    Add_synthAudioProcessorEditor (Add_synthAudioProcessor&);
    ~Add_synthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Add_synthAudioProcessor& audioProcessor;
    
    
    juce::Slider gainMIDISlider;
    juce::Label gainMIDILabel;
    
    juce::Slider gain1Slider;
    juce::Label gain1Label;
    
    juce::Slider freq1Slider;
    juce::Label freq1Label;
    
    juce::Slider gain2Slider;
    juce::Label gain2Label;
    
    juce::Slider freq2Slider;
    juce::Label freq2Label;
    
    juce::Slider gain3Slider;
    juce::Label gain3Label;
    
    juce::Slider freq3Slider;
    juce::Label freq3Label;
    
    
    void sliderValueChanged( juce::Slider * slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Add_synthAudioProcessorEditor)
};
