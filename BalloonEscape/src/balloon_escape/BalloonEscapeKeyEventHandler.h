/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BalloonEscapeKeyEventHandler.h

	This is a custom key event handler. Each game can choose
	to use different keyboard keys and respond differently to when
	they are pressed. This class will handle key presses for
	this particular game following the KeyEventHandler pattern.
*/

#pragma once
#include "balloon_escape_VS\stdafx.h"
#include "sssf\input\KeyEventHandler.h"

class Game;

class BalloonEscapeKeyEventHandler : public KeyEventHandler
{
public:
	BalloonEscapeKeyEventHandler()		{}
	~BalloonEscapeKeyEventHandler()		{}
	void handleKeyEvents(Game *game);
};