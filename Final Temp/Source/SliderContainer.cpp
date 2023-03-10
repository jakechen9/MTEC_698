/*
  ==============================================================================

    SliderContainer.cpp
    Created: 9 Mar 2023 4:26:53pm
    Author:  程

  ==============================================================================
*/

#include "SliderContainer.h"

SliderContainer::SliderContainer()
{
    addAndMakeVisible(mSlider);
    addAndMakeVisible(mLabel);
    
    mLabel.setJustificationType(juce::Justification::centred);
}

void SliderContainer::setParameterToControl(juce::AudioProcessorValueTreeState &inVTS, const juce::String &inParamID)
{
    mLabel.setText(inParamID, juce::dontSendNotification);
    mAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(inVTS, inParamID, mSlider));
}

void SliderContainer::resized()
{
    auto bounds = getLocalBounds();
    mSlider.setBounds(bounds.removeFromTop(getHeight()*.8));
    mLabel.setBounds(bounds);
}
