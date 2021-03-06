/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BalloonEscapeTextGenerator.h

	This class is a custom text generator for the EmptyGame
	application. Basically, by defining the initText and updateText
	methods, we can have it display whatever text we like.
*/

#pragma once
#include "balloon_escape_VS\stdafx.h"
#include "sssf\text\TextGenerator.h"

class BalloonEscapeTextGenerator : public TextGenerator
{
private:
	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring textToGenerate;

public:
	// NOTHING TO INITIALIZE OR DESTROY
	BalloonEscapeTextGenerator()	{}
	~BalloonEscapeTextGenerator()	{}

	// DEFINED IN BalloonEscapeTextGenerator.cpp
	void appendMouseCoords(Game *game);
	void initText(Game *game);
	void updateText(Game *game);
};