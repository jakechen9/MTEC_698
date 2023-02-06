#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (500, 500);
    startTimerHz(30);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // background colour
    g.fillAll(juce::Colours::black);
    
    // dots colour
    g.setColour(juce::Colours::yellow);
    
    // dots size
    float dot_size = 2;
    
    for (int x = 0; x< getWidth(); x += 3){
        float phase = (float)x / (float)getWidth();
        phase += tGlobalphase;
        float offset_height = getHeight() * .25f;
        
        // triangle wave form
        // float sin_y = (2.0f / juce::MathConstants<float>::pi) * asin(sinf(2.0f * phase * juce::MathConstants<float>::twoPi));
        
        // other wave form 1
        // float sin_y = sinf(2.0f * phase * juce::MathConstants<float>::twoPi) + (1.0f/3.0f) * sinf(3.0f * (2.0f * phase * juce::MathConstants<float>::twoPi)) + (1.0f/5.0f) * sinf(5.0f * (2.0f * phase * juce::MathConstants<float>::twoPi)) + (1.0f/7.0f) * sinf(7.0f * (2.0f * phase * juce::MathConstants<float>::twoPi));
        
        // other wave form 2
        float sin_y = 0.5f * (sinf(nMod * phase * juce::MathConstants<float>::twoPi) + 1.0f + sinf((nMod-2) * phase * juce::MathConstants<float>::twoPi) + 4.0f - 5.0f);
        
        
        float offset_y = offset_height * sin_y;
        g.drawLine(x, getHeight()/2, x, getHeight()/2 + offset_y);
        g.fillEllipse(x - dot_size/2.f, getHeight()/2 - dot_size/2.f + offset_y, dot_size, dot_size);
    }
}

void MainComponent::timerCallback()
{
    // set up speed
    tGlobalphase += 0.005;
    nMod += 0.06f;
    if (nMod > 20.f) {
        nMod -= 20.f;
    }
    
    repaint();
}
