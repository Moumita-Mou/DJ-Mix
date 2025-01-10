/*
  ==============================================================================

    DeckGUI.cpp
    Created: 3 Feb 2022 9:32:26pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
	             AudioFormatManager & formatManagerToUse,
	             AudioThumbnailCache & cacheToUse
	     ) 
	      : player(_player),
	        waveformDisplay(formatManagerToUse, cacheToUse)
{
	//attach components : buttons
	addAndMakeVisible(playButton);
	addAndMakeVisible(stopButton);
	addAndMakeVisible(loadButton);
	addAndMakeVisible(pauseButton);
	addAndMakeVisible(loopButton);
	addAndMakeVisible(markerButton1);
	addAndMakeVisible(markerButton2);

	//attach components : sliders
	addAndMakeVisible(volSlider);
	addAndMakeVisible(speedSlider);
	addAndMakeVisible(posSlider);
	
	//attach components : labels
	addAndMakeVisible(volLabel);
	addAndMakeVisible(speedLabel);
	addAndMakeVisible(posLabel);

	//attach audio-thumbnails
	addAndMakeVisible(waveformDisplay);

	//add listeners
	markerButton1.addListener(this);
	markerButton2.addListener(this);
	playButton.addListener(this);
	stopButton.addListener(this);
	pauseButton.addListener(this);
	loadButton.addListener(this);
	loopButton.addListener(this);
	volSlider.addListener(this);
	speedSlider.addListener(this);
	posSlider.addListener(this);

	//Customization of components
	volSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);

	volSlider.setColour(Slider::trackColourId, Colours::purple);
	speedSlider.setColour(Slider::thumbColourId, Colours::purple);
	speedSlider.setColour(Slider::trackColourId, Colours::purple);

	playButton.setColour(TextButton::buttonColourId, Colours::forestgreen);
	stopButton.setColour(TextButton::buttonColourId, Colours::salmon);
	pauseButton.setColour(TextButton::buttonColourId, Colours::gold);
	loopButton.setColour(TextButton::buttonColourId, Colours::rebeccapurple);
	loadButton.setColour(TextButton::buttonColourId, Colours::black);
	posSlider.setColour(Slider::trackColourId, Colours::purple);
	posSlider.setColour(Slider::thumbColourId, Colours::purple);
	markerButton1.setColour(TextButton::buttonColourId, Colours::black);
	markerButton2.setColour(TextButton::buttonColourId, Colours::black);

	//Volume Slider Configurations
	volSlider.setRange(0.0, 5.0);
	volSlider.setNumDecimalPlacesToDisplay(1);
	volSlider.setValue(1.00);
	volSlider.setTextBoxStyle(Slider::TextBoxBelow,
							  false,
							  50,
							  volSlider.getTextBoxHeight()
							  );
	volLabel.setText("Volume", dontSendNotification);
	volLabel.attachToComponent(&volSlider, true);
	
	//Position Slider Configuration
	posSlider.setRange(0.0, 1.0);
	posSlider.setNumDecimalPlacesToDisplay(3);
	posSlider.setTextBoxStyle(Slider::TextBoxLeft,
							  false,
							  50,
							  posSlider.getTextBoxHeight()
							  );
	posLabel.setText("Position", dontSendNotification);
	posLabel.attachToComponent(&posSlider, true);

	//Speed Slider Configuration
	speedSlider.setRange(0.025, 5.000);
	speedSlider.setValue(1.000);
	speedSlider.setNumDecimalPlacesToDisplay(3);
	speedSlider.setTextBoxStyle(Slider::TextBoxLeft,
								false,
								50,
								speedSlider.getTextBoxHeight()
								);
	speedLabel.setText("Speed", dontSendNotification);
	speedLabel.attachToComponent(&speedSlider, true);

	startTimer(500);

}

DeckGUI::~DeckGUI()
{
	stopTimer();
}

void DeckGUI::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                Justification::centred - 55 , true);   // draw some placeholder text
}

void DeckGUI::resized()
{
	double rowH = getHeight() / 8;
	double columnW = getWidth() / 3;
	double quaterW = getWidth() / 4;
	
	//determining size of plaayback control components
	playButton.setBounds(0, 0, columnW, rowH);
	pauseButton.setBounds(columnW, 0, columnW, rowH);
	stopButton.setBounds(columnW * 2, 0, columnW, rowH);
	loadButton.setBounds(0, rowH * 7, getWidth(), rowH);
	markerButton1.setBounds(0, rowH * 1, quaterW, rowH);
	loopButton.setBounds(quaterW, rowH * 1, quaterW * 2, rowH);
	markerButton2.setBounds(quaterW * 3, rowH * 1, quaterW, rowH);
	speedSlider.setBounds(70, rowH * 3, getWidth()/2, rowH);
	posSlider.setBounds(70, rowH * 4, getWidth()/2, rowH);
	waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
	volSlider.setBounds(getWidth() - 50, getHeight()/4, getWidth()/12, rowH * 3);
}

void DeckGUI::buttonClicked(Button* button)
{
	if (button == &playButton)
	{
		player->start();
	}

	if (button == &pauseButton)
	{
		player->pause();
	}

	if (button == &stopButton)
	{  	
		player->stop();
		marked_Pos.clear(); //remove all the saved marked_Pos

		// set the mark button color back to normal
		markerButton1.setColour(TextButton::buttonColourId, Colours::black);
		markerButton2.setColour(TextButton::buttonColourId, Colours::black);
		
	}

	if (button == &loadButton)
	{
		FileChooser chooser{ "select a file...." };
		if (chooser.browseForFileToOpen())
		{
			player->loadURL(URL{ chooser.getResult()});
			waveformDisplay.loadURL(URL{ chooser.getResult() });
		}

	}

	if (button == &loopButton)
	{
		double currentVolValue = volSlider.getValue();
		
        for (double i = 0.0; i < volSlider.getValue() / 0.09; i++)
		{
			player->setGain(volSlider.getValue() - i * 0.09);
			Time::waitForMillisecondCounter(Time::getMillisecondCounter() + 130); //Loop iteration is delayed, giving a fadeout effect.
		}
		
		player->setGain(currentVolValue);
		marked_Pos.clear(); //remove all the saved marked_Pos
		
	    // set the mark button color back to normal
		markerButton1.setColour(TextButton::buttonColourId, Colours::black);
		markerButton2.setColour(TextButton::buttonColourId, Colours::black);
		
		//audio thumbnails drawn when song is looped
		waveformDisplay.loadURL(loop);
		player->loadURL(loop);
		player->start();
		
	}

	if (button == &markerButton1)
	{
		if (mark("markerButton1")) // if mark button clicked...
		{
			button->setColour(TextButton::buttonColourId, Colours::lightgrey);
		}
	}
	if (button == &markerButton2)
	{
		if (mark("markerButton2")) // if mark button clicked...
		{
			button->setColour(TextButton::buttonColourId, Colours::lightgrey);
		}
	}

	

}

void DeckGUI::sliderValueChanged(Slider* slider)
{
	if (slider == &volSlider)
	{
		std::cout << "vol slider moved" << slider->getValue() << std::endl;
		player->setGain(slider->getValue());

	}

	if (slider == &speedSlider)
	{
		std::cout << "speed slider moved" << slider->getValue() << std::endl;
		player->setSpeed(slider->getValue());
	}

	if (slider == &posSlider)
	{
		std::cout << "pos slider moved" << slider->getValue() << std::endl;
		player->setPositionRelative(slider->getValue());
	}
}

bool DeckGUI::isInterestedInFileDrag(const StringArray &files)
{
	return true; 
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y)
{
	if(files.size() == 1)
	{
		player->loadURL(URL{File{files[0]}});
		waveformDisplay.loadURL(URL{ File{files[0]} });
	}
	
}

void DeckGUI::loadFile(URL audioURL)
{

		loop = audioURL;
		loaded = true;
		trackName = loop.getFileName();
		repaint(); 
	
		if(playing)
		{
			player->loadURL(audioURL);
			waveformDisplay.loadURL(audioURL);
		}
}

void DeckGUI::timerCallback()
{
	waveformDisplay.setPositionRelative(
		            player->getPositionRelative());
}

bool DeckGUI::mark(std::string mark_Stamp)
{
	std::map<std::string, double>::iterator it;
	it = marked_Pos.find(mark_Stamp);
	if (player->getPositionRelative() > 0.0) // a mark point can be saved if a song is playing.
	{
		if (it == marked_Pos.end())
		{
			marked_Pos[mark_Stamp] = player->getPositionRelative();
		}
		else
		{
			player->setPositionRelative(marked_Pos[mark_Stamp]);
		}
	}
	else
	{
		return false;
	}
	return true;
}



