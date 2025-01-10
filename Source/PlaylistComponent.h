/*
  ==============================================================================

    PlaylistComponent.h
    Created: 14 Feb 2022 9:18:57pm
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Music.h"
#include "DeckGUI.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent    : public Component,
	                         public TableListBoxModel,
	                         public Button::Listener,
	                         public TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1,
					  DeckGUI* _deckGUI2,
					  DJAudioPlayer* _playerForParsingMetaData
		             );
    ~PlaylistComponent();

    void paint (Graphics&) override;
    void resized() override;

	int getNumRows() override;
	void paintRowBackground(Graphics &, 
		                      int rowNumber, 
		                      int width, 
		                      int height, 
		                      bool rowIsSelected) override;
	void paintCell(Graphics &,
		              int rowNumber,
		              int columnId,
		              int width,
		              int height,
		              bool rowIsSelected) override;
	
	Component* refreshComponentForCell(
						int rowNumber,
						int columnId,
						bool rowIsSelected,
						Component *existingComponentToUpdate) override;

	void buttonClicked(Button *button) override;

private:

	std::vector<Music> songs;
	TextButton importBtn{ "ADD AUDIO FILES TO PLAYLIST" };
    TextEditor searchArea;
	TableListBox playlist;
	TextButton addToPlayer1Button{ "LOAD TO DECK 1" };
	TextButton addToPlayer2Button{ "LOAD TO DECK 2" };

	DeckGUI* deckGUI1;
	DeckGUI* deckGUI2;
	DJAudioPlayer* playerForParsingMetaData;

	String getLength(URL audioURL);
	String secondsToMinutes(double seconds);

	void addToPlaylist();
	void searchInPlaylist(String searchInput);
	int  locateInPlaylist(String searchInput);
	void savePlaylist();
	void loadPlaylist();
	void removeFromPlaylist(int id);
	bool isInSongs(String fileNameWithoutExtension);
	void loadInApp(DeckGUI* deckGUI);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
