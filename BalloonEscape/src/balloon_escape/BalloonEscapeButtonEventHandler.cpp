/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BalloonEscapeButtonEventHandler.cpp

	See BalloonEscapeButtonEventHandler.h for a class description.
*/

#include "balloon_escape_VS\stdafx.h"
#include "balloon_escape\BalloonEscape.h"
#include "balloon_escape\BalloonEscapeButtonEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"

void BalloonEscapeButtonEventHandler::handleButtonEvents(	Game *game, 
													wstring command)
{
	// THE USER PRESSED THE Exit BUTTON ON THE MAIN MENU,
	// SO LET'S SHUTDOWN THE ENTIRE APPLICATION
	if (command.compare(W_EXIT_COMMAND) == 0)
	{
		game->shutdown();
	}
	// THE USER PRESSED THE MOUSE BUTTON ON THE SPLASH
	// SCREEN, SO LET'S GO TO THE MAIN MENU
	else if (command.compare(W_GO_TO_MM_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToMainMenu();
		PlaySound(L"data/sounds/start.wav", NULL, SND_FILENAME|SND_ASYNC);
	}
	// THE USER PRESSED THE Start BUTTON ON THE MAIN MENU,
	// SO LET'S START THE GAME FROM THE FIRST LEVEL
	else if (command.compare(W_START_COMMAND) == 0)
	{
		game->setCurrentLevel(W_LEVEL_1_NAME,W_LEVEL_1_DIR);
		game->startGame();
		PlaySound(L"data/sounds/theme.wav", NULL, SND_FILENAME|SND_ASYNC);
	}
	// THE USER PRESSED THE Quit BUTTON ON THE IN-GAME MENU,
	// SO LET'S UNLOAD THE LEVEL AND RETURN TO THE MAIN MENU
	else if (command.compare(W_QUIT_COMMAND) == 0)
	{
		game->quitGame();
		PlaySound(L"data/sounds/jump.wav", NULL, SND_FILENAME|SND_ASYNC);
	}
	else if (command.compare(W_HELP_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->Help();
		PlaySound(L"data/sounds/jump.wav", NULL, SND_FILENAME|SND_ASYNC);
	}
	else if (command.compare(W_ABOUT_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->About();
		PlaySound(L"data/sounds/jump.wav", NULL, SND_FILENAME|SND_ASYNC);
	}
}