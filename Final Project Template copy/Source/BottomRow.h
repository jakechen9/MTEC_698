/*
  ==============================================================================

    BottomRow.h
    Created: 18 Mar 2023 4:38:17pm
    Author:  程

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "SliderContainer.h"

class BottomRow : public juce::Component
{
public:
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    juce::Label mDelaySectionTitle;
    SliderContainer mDelayMix;
    SliderContainer mDelayTime;
    SliderContainer mDelaySpread;
    SliderContainer mDelayFeedback;
    SliderContainer mDelayWidth;
    SliderContainer mDelayLowpass;
    SliderContainer mDelayHighpass;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BottomRow)
};

