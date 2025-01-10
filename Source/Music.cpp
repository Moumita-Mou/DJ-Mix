/*
  ==============================================================================

    Music.cpp
    Created: 20 Feb 2022 1:46:02am
    Author:  user

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Music.h"
#include <filesystem>

Music::Music(File _file) : file(_file),
						   title(_file.getFileNameWithoutExtension()),
						   URL(juce::URL{_file})
{
	
}

/**objects comparison by title*/
bool Music::operator==(const String& other) const
{
	return title == other;
}