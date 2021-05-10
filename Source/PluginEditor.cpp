/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FM_SynthAudioProcessorEditor::FM_SynthAudioProcessorEditor (FM_SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    
    
    gainLabel.setText("Gain Index", juce::dontSendNotification);
    
    gainSlider.setRange(0.0,1.0,0.1);
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gainSlider.addListener(this);

    addAndMakeVisible(gainSlider);
    addAndMakeVisible(gainLabel);
    
    freqLabel.setText("Freq Index", juce::dontSendNotification);
    
    freqSlider.setRange(-250,250,1);
    freqSlider.setValue(0);
    freqSlider.setSliderStyle(juce::Slider::Rotary);
    freqSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    freqSlider.addListener(this);

    addAndMakeVisible(freqSlider);
    addAndMakeVisible(freqLabel);
}

FM_SynthAudioProcessorEditor::~FM_SynthAudioProcessorEditor()
{
}

//==============================================================================
void FM_SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void FM_SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    
    gainLabel.setBounds(100,50,130,20);
    gainSlider.setBounds(100,80,100,100);
    
    freqLabel.setBounds(300,50,130,20);
    freqSlider.setBounds(300,80,100,100);
}

void FM_SynthAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.set_gain(gainSlider.getValue());
    }
    
    if (slider == &freqSlider)
    {
        audioProcessor.set_freq(freqSlider.getValue());
    }
}
