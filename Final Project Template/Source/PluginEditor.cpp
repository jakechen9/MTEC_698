/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
Week6AssignmentAudioProcessorEditor::Week6AssignmentAudioProcessorEditor (Week6AssignmentAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel(&mLookAndFeel);
    auto& tree_state = audioProcessor.getParameterManager()->getTreeState();

    for (int i = 0; i < audioProcessor.getParameters().size(); i++) {
            mSliderContainers.add(new SliderContainer());
            mSliderContainers[i]->setParameterToControl(tree_state, ParameterIDStrings[i]);
            addAndMakeVisible(mSliderContainers[i]);
    }
    setSize (1100, 720);
}

Week6AssignmentAudioProcessorEditor::~Week6AssignmentAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void Week6AssignmentAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Week6AssignmentAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
        int num_slider = mSliderContainers.size();
        for (int i = 0; i < mSliderContainers.size(); i++) {
            mSliderContainers[i]->setBounds(bounds.removeFromTop(getHeight()/num_slider));
        }
}

