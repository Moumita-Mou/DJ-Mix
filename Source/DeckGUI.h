/*
  ==============================================================================

    DeckGUI.h
    Created: 3 Feb 2022 9:32:26pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include <map>

//==============================================================================
/*
*/
class DeckGUI    : public Component,
	               public Button::Listener,
	               public Slider::Listener,
	               public FileDragAndDropTarget,
	               public Timer
{
public:
	DeckGUI( 
		     DJAudioPlayer* player,
		     AudioFormatManager & formatManagerToUse,
		     AudioThumbnailCache & cacheToUse);
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;
	void buttonClicked(Button* button) override;
	void sliderValueChanged(Slider* slider) override;
	bool isInterestedInFileDrag(const StringArray &files) override;
	void filesDropped(const StringArray &files, int x, int y) override;
	void timerCallback() override;

	
private:
	
	std::map<std::string, double> marked_Pos;  //map marked positions within song played

	bool mark(std::string mark_Stamp);
	bool loaded;
	bool playing;
	
	//playback control buttons
	TextButton playButton{ "PLAY" };
	TextButton pauseButton{ "PAUSE" };
	TextButton loadButton{ "LOAD" };
	TextButton stopButton{ "STOP" };
	TextButton markerButton1{ "MARKER A" };
	TextButton markerButton2{ "MARKER B" };
	TextButton loopButton{ "Loop" };

	//playback control sliders
	Slider volSlider;
	Slider speedSlider;
	Slider posSlider;
	
	//playback control slider labels
	Label volLabel;
	Label speedLabel;
	Label posLabel;
	
	Path LoopButtonPath;
	Path LoopEndButtonPath;
	
	URL loop;
	String trackName;
	
	DJAudioPlayer* player;
	WaveformDisplay waveformDisplay;

	void loadFile(URL audioURL);

	SharedResourcePointer< TooltipWindow > tipWindow;

	friend class PlaylistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
