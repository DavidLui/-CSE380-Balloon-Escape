/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BalloonEscapeGame.cpp

	This is a test game application, a game that demonstrates use of the 
	SideScrollerFramework to make a little scrolling, interactive demo. It
	demonstrates the rendering of images and text as well as responding to
	key presses and button cicks. Students should make their own named game
	applictions using a similar pattern, gradually adding other components,
	like additional gui controls, tiles, sprites, ai, and physics.
 */

#include "balloon_escape_VS\stdafx.h"
// BalloonEscape GAME INCLUDES
#include "balloon_escape\BalloonEscapeButtonEventHandler.h"
#include "balloon_escape\BalloonEscapeCollisionListener.h"
#include "balloon_escape\BalloonEscapeDataLoader.h"
#include "balloon_escape\BalloonEscape.h"
#include "balloon_escape\BalloonEscapeKeyEventHandler.h"
#include "balloon_escape\BalloonEscapeTextGenerator.h"
#include "Box2D.h"

// GAME OBJECT INCLUDES
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\gui\ScreenGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\os\GameOS.h"
#include "sssf\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "sssf\platforms\Windows\WindowsOS.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"
// DIRECTX INCLUDES
#include "sssf\platforms\DirectX\DirectXGraphics.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"

/*
	WinMain - This is the application's starting point. In this method we will construct a Game object, 
	then initialize all the platform-dependent technologies, then construct all the custom data for our 
	game, and then initialize the Game with	our custom data. We'll then start the game loop.
*/

struct Nums
{

	int num1;
	int num2;
};
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{

	b2Vec2 gravity(0.0f, -10.0f);


	// CREATE THE GAME
	Game *balloonEscapeGame = new Game();
	// FIRST WE'LL SETUP THE DATA LOADER, SINCE IT MAY NEED TO READ
	// IN DATA TO SETUP OTHER STUFF
	BalloonEscapeDataLoader *balloonEscapeDataLoader = new BalloonEscapeDataLoader();
	balloonEscapeDataLoader->initWinHandle(hInstance, nCmdShow);
	balloonEscapeGame->setDataLoader(balloonEscapeDataLoader);
	balloonEscapeDataLoader->loadGame(balloonEscapeGame, W_INIT_FILE);
	
	// WHAT WE SHOULD BE DOING HERE IS LOADING THE GAME DATA FROM FILES. THIS
	// MEANS THE GUIS THEMSELVES AS WELL AS THE LEVELS. THAT WILL BE LEFT
	// FOR BECHMARK HWS. FOR NOW WE WILL JUST HARD CODE THE LOADING OF THE GUI

	// LOAD THE GUI STUFF, AGAIN, NOTE THAT THIS SHOULD REALLY
	// BE DONE FROM A FILE, NOT HARD CODED
	balloonEscapeDataLoader->loadGUI(balloonEscapeGame, W_GUI_INIT_FILE);

	// SPECIFY WHO WILL HANDLE BUTTON EVENTS
	BalloonEscapeButtonEventHandler *balloonEscapeButtonHandler = new BalloonEscapeButtonEventHandler();
	GameGUI *gui = balloonEscapeGame->getGUI();
	gui->registerButtonEventHandler((ButtonEventHandler*)balloonEscapeButtonHandler);
	// SPECIFY WHO WILL HANDLE KEY EVENTS
	BalloonEscapeKeyEventHandler *balloonEscapeKeyHandler = new BalloonEscapeKeyEventHandler();
	balloonEscapeGame->getInput()->registerKeyHandler((KeyEventHandler*)balloonEscapeKeyHandler);

	// THIS WILL HANDLE PHYSICS COLLISION EVENTS
	BalloonEscapeCollisionListener *balloonEscapeCollisionListener = new BalloonEscapeCollisionListener();
	balloonEscapeGame->getGSM()->getPhysics()->setCollisionListener(balloonEscapeCollisionListener);

	// START THE GAME LOOP
	balloonEscapeGame->runGameLoop();

	// GAME'S OVER SHUTDOWN ALL THE STUFF WE CONSTRUCTED HERE
	delete (WindowsOS*)balloonEscapeGame->getOS();
	delete (WindowsInput*)balloonEscapeGame->getInput();
	delete (WindowsTimer*)balloonEscapeGame->getTimer();
	delete (DirectXGraphics*)balloonEscapeGame->getGraphics();
	delete (BalloonEscapeTextGenerator*)balloonEscapeGame->getText()->getTextGenerator();
	delete balloonEscapeButtonHandler;
	delete balloonEscapeKeyHandler;
	delete balloonEscapeGame;

	// AND RETURN
	return 0;
}