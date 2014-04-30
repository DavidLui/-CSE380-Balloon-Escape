/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BalloonEscapeButtonEventHandler.h

	This is a custom button event handler. Each game can choose
	to use different buttons and respond differently to when
	buttons are pressed. This class will handle button presses for
	the BalloonEscapeGame following the ButtonEventHandler pattern.
*/

#pragma once
#include "balloon_escape_VS\stdafx.h"
#include "sssf\input\ButtonEventHandler.h"

class Game;

class BalloonEscapeButtonEventHandler: public ButtonEventHandler
{
public:
	// AS-IS, THIS CLASS HAS NO DATA, SO THERE IS NOTHING
	// TO INITIALIZE OR DESTROY
	BalloonEscapeButtonEventHandler()	{}
	~BalloonEscapeButtonEventHandler()	{}

	// DEFINED INSIDE BalloonEscapeButtonEventHandler.cpp
	void handleButtonEvents(Game *game, 
							wstring command);
};