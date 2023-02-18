/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week3SineGeneratorAudioProcessorEditor::Week3SineGeneratorAudioProcessorEditor (Week3SineGeneratorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSlider.setRange(5.f, 20.f);
    mSlider.setValue(audioProcessor.getMod());
    
    mSlider.onValueChange = [this] () {
            audioProcessor.setMod(mSlider.getValue());
    };
    addAndMakeVisible(mSlider);
    setSize (400, 300);
    
}

Week3SineGeneratorAudioProcessorEditor::~Week3SineGeneratorAudioProcessorEditor()
{
}

//==============================================================================
void Week3SineGeneratorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void Week3SineGeneratorAudioProcessorEditor::resized()
{
    mSlider.setBounds(getLocalBounds());
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth(), 20);
}

void Week3SineGeneratorAudioProcessorEditor::timerCallback()
{
    
}
