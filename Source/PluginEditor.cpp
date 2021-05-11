/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Add_synthAudioProcessorEditor::Add_synthAudioProcessorEditor (Add_synthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 800);
    
    
    gainMIDILabel.setText("MIDI Oscillator Gain", juce::dontSendNotification);
    
    gainMIDISlider.setRange(0.0,1.0,0.1);
    gainMIDISlider.setSliderStyle(juce::Slider::Rotary);
    gainMIDISlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gainMIDISlider.addListener(this);

    addAndMakeVisible(gainMIDISlider);
    addAndMakeVisible(gainMIDILabel);
    
    gain1Label.setText("Oscillator 1 Gain", juce::dontSendNotification);
    
    gain1Slider.setRange(0.0,1.0,0.1);
    gain1Slider.setSliderStyle(juce::Slider::Rotary);
    gain1Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gain1Slider.addListener(this);

    addAndMakeVisible(gain1Slider);
    addAndMakeVisible(gain1Label);
    
    freq1Label.setText("Osc 1 Freq Offset", juce::dontSendNotification);
    
    freq1Slider.setRange(-1.0,1.0,0.01);
    freq1Slider.setValue(0.0);
    freq1Slider.setSliderStyle(juce::Slider::Rotary);
    freq1Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    freq1Slider.addListener(this);

    addAndMakeVisible(freq1Slider);
    addAndMakeVisible(freq1Label);
    
    gain2Label.setText("Oscillator 2 Gain", juce::dontSendNotification);
    
    gain2Slider.setRange(0.0,1.0,0.1);
    gain2Slider.setSliderStyle(juce::Slider::Rotary);
    gain2Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gain2Slider.addListener(this);

    addAndMakeVisible(gain2Slider);
    addAndMakeVisible(gain2Label);
    
    freq2Label.setText("Osc 2 Freq Offset", juce::dontSendNotification);
    
    freq2Slider.setRange(-1.0,1.0,0.01);
    freq2Slider.setValue(0.0);
    freq2Slider.setSliderStyle(juce::Slider::Rotary);
    freq2Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    freq2Slider.addListener(this);

    addAndMakeVisible(freq2Slider);
    addAndMakeVisible(freq2Label);
    
    gain3Label.setText("Oscillator 3 Gain", juce::dontSendNotification);
    
    gain3Slider.setRange(0.0,1.0,0.1);
    gain3Slider.setSliderStyle(juce::Slider::Rotary);
    gain3Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    gain3Slider.addListener(this);

    addAndMakeVisible(gain3Slider);
    addAndMakeVisible(gain3Label);
    
    freq3Label.setText("Osc 3 Freq Offset", juce::dontSendNotification);
    
    freq3Slider.setRange(-1.0,1.0,0.01);
    freq3Slider.setValue(0.0);
    freq3Slider.setSliderStyle(juce::Slider::Rotary);
    freq3Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    freq3Slider.addListener(this);

    addAndMakeVisible(freq3Slider);
    addAndMakeVisible(freq3Label);
}

Add_synthAudioProcessorEditor::~Add_synthAudioProcessorEditor()
{
}

//==============================================================================
void Add_synthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void Add_synthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    
    gainMIDILabel.setBounds(180,50,130,20);
    gainMIDISlider.setBounds(200,80,100,100);
    
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

void Add_synthAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
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
