/*
  ==============================================================================

    WaveformDisplay.h
    Created: 4 Feb 2022 9:35:51pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay    : public Component,
	                       public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager & formatManagerToUse,
		            AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay();

    void paint (Graphics&) override;
    void resized() override;

	void changeListenerCallback(ChangeBroadcaster *source) override;

	void loadURL(URL audioURL);
	/*set relative position of playhead*/
	void setPositionRelative(double pos);

private:

	AudioThumbnail audioThumb;
	bool fileLoaded;
	double position;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
