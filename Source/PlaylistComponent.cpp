/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 14 Feb 2022 9:18:57pm
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"


//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1,
				   DeckGUI* _deckGUI2,
				   DJAudioPlayer* _playerForParsingMetaData
	               ) : deckGUI1(_deckGUI1),
				       deckGUI2(_deckGUI2),
				       playerForParsingMetaData(_playerForParsingMetaData)
{
	// attach components
	addAndMakeVisible(importBtn);
	addAndMakeVisible(searchArea);
	addAndMakeVisible(playlist);
	addAndMakeVisible(addToPlayer1Button);
	addAndMakeVisible(addToPlayer2Button);

	// attach listeners
	importBtn.addListener(this);
	searchArea.addListener(this);
	addToPlayer1Button.addListener(this);
	addToPlayer2Button.addListener(this);

	//customisation of buttons
	importBtn.setColour(TextButton::buttonColourId, Colours::darkolivegreen);
    addToPlayer1Button.setColour(TextButton::buttonColourId, Colours::darkolivegreen);
	addToPlayer2Button.setColour(TextButton::buttonColourId, Colours::darkolivegreen);


	// searchArea settings
	searchArea.setColour(TextEditor::backgroundColourId, Colours::black);
	searchArea.setTextToShowWhenEmpty("TYPE TO SEARCH (Hit 'Enter' to submit)", Colours::royalblue);
	searchArea.onReturnKey = [this] {searchInPlaylist(searchArea.getText()); };

	// setup table to load playlist from file
	playlist.getHeader().addColumn("Track Title", 1, 1);
	playlist.getHeader().addColumn("Length", 2, 1);
	playlist.getHeader().addColumn("", 3, 1);
	playlist.setModel(this);
	loadPlaylist();
	
}

PlaylistComponent::~PlaylistComponent()
{
	savePlaylist();
}

void PlaylistComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("MUSIC PLAYLIST", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{

	importBtn.setBounds(0, 0, getWidth(), getHeight() / 8);
	playlist.setBounds(0, getHeight() / 8, getWidth(), 5 * getHeight() / 8);
	searchArea.setBounds(0, 6 * getHeight() / 8, getWidth(), getHeight()/8);
	addToPlayer1Button.setBounds(0, 7 * getHeight() / 8, getWidth() / 2, getHeight() / 8);
	addToPlayer2Button.setBounds(getWidth() / 2, 7 * getHeight() / 8, getWidth() / 2, getHeight() / 8);

	//add columns
	playlist.getHeader().setColumnWidth(1, getWidth() / 2);
	playlist.getHeader().setColumnWidth(2, getWidth() / 4);
	playlist.getHeader().setColumnWidth(3, getWidth() / 6);
}

int PlaylistComponent::getNumRows()
{
	return songs.size(); // get duration of song
}
void PlaylistComponent::paintRowBackground(Graphics& g,
	                     int rowNumber,
	                     int width,
	                     int height,
	                     bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.fillAll(Colours::darkolivegreen); //set color of selected row in playlist
	}
	else {
		g.fillAll(Colours::transparentBlack);
	}

}

void PlaylistComponent::paintCell(Graphics& g,
	                     int rowNumber,
	                     int columnId,
	                     int width,
	                     int height,
	                     bool rowIsSelected)
{

	if (rowNumber < getNumRows())
	{
		if (columnId == 1)
		{
			g.drawText(songs[rowNumber].title,
				2,
				0,
				width - 4,
				height,
				juce::Justification::centredLeft,
				true
				);
		}
		if (columnId == 2)
		{
			g.drawText(songs[rowNumber].length,
				2,
				0,
				width - 4,
				height,
				juce::Justification::centred,
				true
				);
		}
	}
}

Component* PlaylistComponent::refreshComponentForCell(
													int rowNumber,
													int columnId,
													bool rowIsSelected,
													Component *existingComponentToUpdate)
{
	if (columnId == 3) // create remove button
	{
		if (existingComponentToUpdate == nullptr)
		{
			TextButton* btn = new TextButton{ "REMOVE" };
			String id{std::to_string(rowNumber)};
			btn->setComponentID(id);
			btn->addListener(this);
			btn->setColour(TextButton::buttonColourId, Colours::black);
			existingComponentToUpdate = btn;
		}
	}
	return existingComponentToUpdate;
}
void PlaylistComponent::buttonClicked(Button *button)
{
	if (button == &importBtn)
	{
		addToPlaylist();
		playlist.updateContent();
	}
	else if (button == &addToPlayer1Button)
	{
		loadInApp(deckGUI1);
	}
	else if (button == &addToPlayer2Button)
	{
		loadInApp(deckGUI2);
	}
	else
	{
		int id = std::stoi(button->getComponentID().toStdString());
		removeFromPlaylist(id);
		playlist.updateContent();
	}
}

void PlaylistComponent::loadInApp(DeckGUI* deckGUI)
{
	int selectedRow{ playlist.getSelectedRow() };
	if (selectedRow != -1)
	{
		deckGUI->loadFile(songs[selectedRow].URL);

	}
	else
	{
		    AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon,
			"Add to Deck Information:",
			"Please select a track to add to deck",
			"OK",
			nullptr
			);
	}
}


void PlaylistComponent::addToPlaylist()
{
	//initialize file chooser
	FileChooser chooser{ "Select files......." };
	if (chooser.browseForMultipleFilesToOpen())
	{
		for (const File& file : chooser.getResults())
		{
			String fileNameWithoutExtension{ file.getFileNameWithoutExtension() };
			if (!isInSongs(fileNameWithoutExtension)) // if song is not loaded
			{
				Music newTrack{ file };
				URL audioURL{ file };
				newTrack.length = getLength(audioURL);
				songs.push_back(newTrack);
				
			}
			else //show alert message
			{
				AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon,
					"Load information:",
					fileNameWithoutExtension + " already loaded",
					"OK",
					nullptr
					);
			}
		}
	}
}

bool PlaylistComponent::isInSongs(String fileNameWithoutExtension)
{
	return (std::find(songs.begin(), songs.end(), fileNameWithoutExtension) != songs.end());
	
}

void PlaylistComponent::removeFromPlaylist(int id)
{
	//remove song from playlist
	songs.erase(songs.begin() + id);
}

String PlaylistComponent::getLength(URL audioURL)
{
	playerForParsingMetaData->loadURL(audioURL);
	double seconds{ playerForParsingMetaData->getLengthInSeconds() };
	String minutes{ secondsToMinutes(seconds) };
	return minutes;
}

String PlaylistComponent::secondsToMinutes(double seconds)
{
	//find seconds and minutes and convert to string
	int secondsRounded{ int(std::round(seconds)) };
	String min{ std::to_string(secondsRounded / 60) };
	String sec{ std::to_string(secondsRounded % 60) };

	if (sec.length() < 2) // if seconds is less than 1 digit
	{
		//add '0' to seconds until seconds becomes length 2
		sec = sec.paddedLeft('0', 2);
	}
	return String{ min + ":" + sec };
}

void PlaylistComponent::searchInPlaylist(String searchInput)
{
	//take search input to search within the playlist
	if (searchInput != "")
	{
		int rowNumber = locateInPlaylist(searchInput);
		playlist.selectRow(rowNumber);
	}
	else
	{
		playlist.deselectAllRows();
	}
}

int PlaylistComponent::locateInPlaylist(String searchInput)
{
	// finds the song in playlist
	auto it = find_if(songs.begin(), songs.end(),
		[&searchInput](const Music& obj) {return obj.title.contains(searchInput); });
	int i = -1;

	if (it != songs.end())
	{
		i = std::distance(songs.begin(), it);
	}

	return i;
}


void PlaylistComponent::savePlaylist()
{
	// make .csv to save playlist
	std::ofstream myplaylist("my-playlist.csv");

	// save playlist to file
	for (Music& t : songs)
	{
		myplaylist << t.file.getFullPathName() << "," << t.length << "\n";
	}
}

void PlaylistComponent::loadPlaylist()
{
	// create input-file stream from saved playlist
	std::ifstream myplaylist("my-playlist.csv");
	std::string filePath;
	std::string length;

	// fetch data, line to line
	if (myplaylist.is_open())
	{
		while (getline(myplaylist, filePath, ',')) {
			File file{ filePath };
			Music newTrack{ file };

			getline(myplaylist, length);
			newTrack.length = length;
			songs.push_back(newTrack);
		}
	}
	myplaylist.close();
}