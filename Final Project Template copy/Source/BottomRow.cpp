/*
  ==============================================================================

    BottomRow.cpp
    Created: 18 Mar 2023 4:38:17pm
    Author:  程

  ==============================================================================
*/

#include "BottomRow.h"

void BottomRow::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(255, 255, 255));
    g.fillRoundedRectangle(0.f, 483.f, 1100.f, 237.f, 0.f);
}

void BottomRow::resized()
{
    auto area = getLocalBounds().reduced(5, 0);
    const int boundHeight = (area.getHeight() - 5) / 3;
    
    mDelayMix.setBounds(area.removeFromTop(boundHeight));
}
