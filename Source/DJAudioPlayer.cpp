/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 1 Feb 2022 12:57:02pm
    Author:  user

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
    : formatManager (_formatManager)
{
	
}
DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	resampleSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
	transportSource.releaseResources();
	resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
	AudioFormatReader* reader = formatManager.createReaderFor(audioURL.createInputStream(false));

	if (reader != nullptr) {
		std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
		transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());
		transportSource.start();
	}

	else { std::cout << "Something went wrong loading the file " << std::endl; }
}
void DJAudioPlayer::setGain(double gain)
{
	if (gain < 0 || gain > 1)
	{
		std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
	}
	else 
	{
	   transportSource.setGain(gain);
	}
	
}
void DJAudioPlayer::setSpeed(double ratio)
{
	if (ratio < 0 || ratio > 10)
	{
		std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 10" << std::endl;
	}
	else
	{
		resampleSource.setResamplingRatio(ratio);
	}
}
void DJAudioPlayer::setPosition(double posInSecs)
{
	transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
	if (pos < 0 || pos > 1.0)
	{
  		std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
	}
	else
	{
		double posInSecs = transportSource.getLengthInSeconds() * pos;
		setPosition(posInSecs);
	}
}

void DJAudioPlayer::start()
{
	transportSource.start();
}
void DJAudioPlayer::pause()
{
	transportSource.stop();
}

void DJAudioPlayer::stop()
{
	transportSource.stop();
	transportSource.setPosition(0.00);
}


double DJAudioPlayer::getPositionRelative()
{
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

double DJAudioPlayer::getLengthInSeconds()
{
	return transportSource.getLengthInSeconds();
}

