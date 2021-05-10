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
    setSize (600, 800);
    
    
    gainMIDILabel.setText("Gain MIDI Index", juce::dontSendNotification);
    
    gainMIDISlider.setRange(0.0,1.0,0.1);
    gainMIDISlider.setSliderStyle(juce::Slider::Rotary);
    gainMIDISlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gainMIDISlider.addListener(this);

    addAndMakeVisible(gainMIDISlider);
    addAndMakeVisible(gainMIDILabel);
    
    gain1Label.setText("Gain 1 Index", juce::dontSendNotification);
    
    gain1Slider.setRange(0.0,1.0,0.1);
    gain1Slider.setSliderStyle(juce::Slider::Rotary);
    gain1Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gain1Slider.addListener(this);

    addAndMakeVisible(gain1Slider);
    addAndMakeVisible(gain1Label);
    
    freq1Label.setText("Freq 1 Index", juce::dontSendNotification);
    
    freq1Slider.setRange(-250,250,1);
    freq1Slider.setValue(0);
    freq1Slider.setSliderStyle(juce::Slider::Rotary);
    freq1Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    freq1Slider.addListener(this);

    addAndMakeVisible(freq1Slider);
    addAndMakeVisible(freq1Label);
    
    gain2Label.setText("Gain 2 Index", juce::dontSendNotification);
    
    gain2Slider.setRange(0.0,1.0,0.1);
    gain2Slider.setSliderStyle(juce::Slider::Rotary);
    gain2Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gain2Slider.addListener(this);

    addAndMakeVisible(gain2Slider);
    addAndMakeVisible(gain2Label);
    
    freq2Label.setText("Freq 2 Index", juce::dontSendNotification);
    
    freq2Slider.setRange(-250,250,1);
    freq2Slider.setValue(0);
    freq2Slider.setSliderStyle(juce::Slider::Rotary);
    freq2Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    freq2Slider.addListener(this);

    addAndMakeVisible(freq2Slider);
    addAndMakeVisible(freq2Label);
    
    gain3Label.setText("Gain 3 Index", juce::dontSendNotification);
    
    gain3Slider.setRange(0.0,1.0,0.1);
    gain3Slider.setSliderStyle(juce::Slider::Rotary);
    gain3Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gain3Slider.addListener(this);

    addAndMakeVisible(gain3Slider);
    addAndMakeVisible(gain3Label);
    
    freq3Label.setText("Freq 3 Index", juce::dontSendNotification);
    
    freq3Slider.setRange(-250,250,1);
    freq3Slider.setValue(0);
    freq3Slider.setSliderStyle(juce::Slider::Rotary);
    freq3Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    freq3Slider.addListener(this);

    addAndMakeVisible(freq3Slider);
    addAndMakeVisible(freq3Label);
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
    
    
    gainMIDILabel.setBounds(100,50,130,20);
    gainMIDISlider.setBounds(100,80,100,100);
    
    gain1Label.setBounds(100,200,130,20);
    gain1Slider.setBounds(100,230,100,100);
    
    freq1Label.setBounds(300,200,130,20);
    freq1Slider.setBounds(300,230,100,100);

    gain2Label.setBounds(100,350,130,20);
    gain2Slider.setBounds(100,380,100,100);
    
    freq2Label.setBounds(300,350,130,20);
    freq2Slider.setBounds(300,380,100,100);
    
    gain3Label.setBounds(100,500,130,20);
    gain3Slider.setBounds(100,530,100,100);
    
    freq3Label.setBounds(300,500,130,20);
    freq3Slider.setBounds(300,530,100,100);
}

void FM_SynthAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &gainMIDISlider)
    {
        audioProcessor.setGainMIDI(gainMIDISlider.getValue());
    }
    
    else if (slider == &gain1Slider)
    {
        audioProcessor.setGain1(gain1Slider.getValue());
    }
    
    else if (slider == &freq1Slider)
    {
        audioProcessor.setFreq1(freq1Slider.getValue());
    }
    
    else if (slider == &gain2Slider)
    {
        audioProcessor.setGain2(gain2Slider.getValue());
    }
    
    else if (slider == &freq2Slider)
    {
        audioProcessor.setFreq2(freq2Slider.getValue());
    }
      
    else if (slider == &gain3Slider)
    {
        audioProcessor.setGain3(gain3Slider.getValue());
    }
    
    else if (slider == &freq3Slider)
    {
        audioProcessor.setFreq3(freq3Slider.getValue());
    }
    
}
