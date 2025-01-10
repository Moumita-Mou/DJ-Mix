/*
  ==============================================================================

    Music.h
    Created: 20 Feb 2022 1:46:02am
    Author:  user

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Music
{
public:
	Music(File _file);
	File file;
	URL URL;
	String title;
	String length;

	bool operator==(const String& other) const; 

};
