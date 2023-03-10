/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderContainer.h"

//==============================================================================
/**
*/
class Week6AssignmentAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week6AssignmentAudioProcessorEditor (Week6AssignmentAudioProcessor&);
    ~Week6AssignmentAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // the slider components
    juce::OwnedArray<SliderContainer> mSliderContainers;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week6AssignmentAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week6AssignmentAudioProcessorEditor)
};
