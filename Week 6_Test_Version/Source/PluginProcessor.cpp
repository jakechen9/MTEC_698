/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week6AssignmentAudioProcessor::Week6AssignmentAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),

        mParameterState (*this, nullptr, juce::Identifier("ParamterState"), getParameterLayout())
        {
            mod1 = mParameterState.getRawParameterValue("Modulation1");
            mod2 = mParameterState.getRawParameterValue("Modulation2");
        }


Week6AssignmentAudioProcessor::~Week6AssignmentAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout Week6AssignmentAudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    // mod1
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Mod1",1),
                                                           "Mod1",
                                                           3.0f,
                                                           20.0f,
                                                           6.0f));
    // mod2
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Mod2",1),
                                                           "Mod2",
                                                           4.0f,
                                                           40.0f,
                                                           8.0f));
    
    return layout;
}


void Week6AssignmentAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mMod_1.reset(sampleRate, 0.01);
    mMod_1.setCurrentAndTargetValue(6.0f);
    mMod_2.reset(sampleRate, 0.01);
    mMod_2.setCurrentAndTargetValue(8.0f);
}

void Week6AssignmentAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mMod_1.setTargetValue(mod1->load());
    mMod_2.setTargetValue(mod2->load());

    for (int sample = 0; sample < buffer.getNumSamples(); sample++){

        // phase
        phase += (60.f / getSampleRate());
        if (phase > 1.f) {
            phase -= 1.f;
        }
        // mod
        float mm1 = mMod_1.getNextValue();
        float mm2 = mMod_2.getNextValue();
        float out_left = (asin(pow(sin(mm1 *juce::MathConstants<float>::twoPi * phase),3)) + asin(pow(sin((mm2 - 1) *juce::MathConstants<float>::twoPi * phase),3))) * 0.125f;
        float out_right = out_left;
        buffer.setSample(0, sample, out_left);
        buffer.setSample(1, sample, out_right);
    }
}


// STATE
//==============================================================================
void Week6AssignmentAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = mParameterState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}


void Week6AssignmentAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mParameterState.replaceState(juce::ValueTree::fromXml(*xmlState));
}



//==============================================================================
const juce::String Week6AssignmentAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week6AssignmentAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week6AssignmentAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week6AssignmentAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week6AssignmentAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week6AssignmentAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week6AssignmentAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week6AssignmentAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week6AssignmentAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week6AssignmentAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================


void Week6AssignmentAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week6AssignmentAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif



//==============================================================================
bool Week6AssignmentAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week6AssignmentAudioProcessor::createEditor()
{
    return new Week6AssignmentAudioProcessorEditor (*this);
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week6AssignmentAudioProcessor();
}
