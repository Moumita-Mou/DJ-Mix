/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h" 
#include "PlaylistComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
	                    
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
	

private:
    //==============================================================================
    // Your private member variables go here...

	AudioFormatManager formatManager;
	AudioThumbnailCache thumbCache{100};

	DJAudioPlayer player1{formatManager};
	DJAudioPlayer player2{formatManager};

	DJAudioPlayer playerForParsingMetaData{ formatManager };

	DeckGUI deckGUI1{&player1, formatManager, thumbCache };
	DeckGUI deckGUI2{&player2, formatManager, thumbCache };
	PlaylistComponent playlistComponent{ &deckGUI1, &deckGUI2, &playerForParsingMetaData };

	MixerAudioSource mixerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
