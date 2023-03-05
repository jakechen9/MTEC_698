/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Week6AssignmentAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Week6AssignmentAudioProcessor();
    ~Week6AssignmentAudioProcessor() override;

    //==============================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

   

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    juce::AudioProcessorValueTreeState& getTreeState() {
            return mParameterState;
        }

private:
    float phase = 0.f;
    std::atomic<float>* mod1 = nullptr;
    std::atomic<float>* mod2 = nullptr;
    juce::AudioProcessorValueTreeState mParameterState;
    juce::LinearSmoothedValue<float> mMod_1;
    juce::LinearSmoothedValue<float> mMod_2;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week6AssignmentAudioProcessor)
};
