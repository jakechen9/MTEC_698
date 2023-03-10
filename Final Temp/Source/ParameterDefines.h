/*
  ==============================================================================

    ParameterDefines.h
    Created: 9 Mar 2023 6:50:54pm
    Author:  程

  ==============================================================================
*/

#pragma once

enum AppParameterID{
    Mod1,
    Mod2,
    TotalNumberParameters
};

static juce::Array<juce::String> ParameterIDStrings{
    "Mod1",
    "Mod2"
};

static juce::Array<juce::String> ParameterMinimum{
    3.f,
    4.f
};

static juce::Array<juce::String> ParameterMaximum{
    20.f,
    40.f
};

static juce::Array<juce::String> ParameterDefault{
    6.f,
    8.f
};

