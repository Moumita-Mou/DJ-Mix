/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 1 Feb 2022 12:57:02pm
    Author:  user

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class DJAudioPlayer : public AudioSource {

     public:

		 DJAudioPlayer(AudioFormatManager& _formatManager);
		 ~DJAudioPlayer();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	void loadURL(URL audioURL);
	void setGain(double gain);
	void setSpeed(double ratio);
	void setPosition(double posInSecs);
	void setPositionRelative(double pos);

	//playback attributes
	void start();
	void stop();
	void pause();

	/**Gets the length of transport source in seconds*/
	double getLengthInSeconds();

	/* get the relative position of playhead*/
	double getPositionRelative();

    private:
		AudioFormatManager& formatManager;
		std::unique_ptr <AudioFormatReaderSource> readerSource;
		AudioTransportSource transportSource;
		ResamplingAudioSource resampleSource{&transportSource, false, 2};



};