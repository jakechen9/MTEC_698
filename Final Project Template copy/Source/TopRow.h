/*
  ==============================================================================

    TopRow.h
    Created: 18 Mar 2023 4:37:55pm
    Author:  程

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
class TopRow : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
};

