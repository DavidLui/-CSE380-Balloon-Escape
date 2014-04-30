#include "balloon_escape_VS\stdafx.h"

// BalloonEscape GAME INCLUDES
#include "balloon_escape\BalloonEscapeButtonEventHandler.h"
#include "balloon_escape\BalloonEscapeDataLoader.h"
#include "balloon_escape\BalloonEscape.h"
#include "balloon_escape\BalloonEscapeKeyEventHandler.h"
#include "balloon_escape\BalloonEscapeTextGenerator.h"

// GAME OBJECT INCLUDES
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\bots\RandomJumpingBot.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\gui\ScreenGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\os\GameOS.h"
#include "sssf\text\GameText.h"
#include "sssf\gui\LifeStatus.h"

// WINDOWS PLATFORM INCLUDES
#include "sssf\platforms\Windows\WindowsOS.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

// DIRECTX INCLUDES
#include "sssf\platforms\DirectX\DirectXGraphics.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"

// TMX MAP LOADING
#include "tmxmi\TMXMapImporter.h"

// ANIMATED SPRITE TYPE LOADING
#include "psti\PoseurSpriteTypesImporter.h"

/*
	loadGame - This method loads the setup game data into the game and
	constructs all the needed objects for the game to work.
*/
void BalloonEscapeDataLoader::loadGame(Game *game, wstring gameInitFile)
{
	// AND LET'S READ IN THE GAME SETUP INFO
	// FIRST LOAD ALL THE PROPERTIES
	map<wstring,wstring> *properties = new map<wstring,wstring>();
	loadGameProperties(game, properties, gameInitFile);

	// WE NEED THE TITLE AND USE_FULLSCREEN_MODE TO INITIALIZE OUR WINDOW
	wstring titleProp = (*properties)[W_TITLE];
	wstring useFullscreenProp = (*properties)[W_USE_FULLSCREEN_MODE];
	bool useFullscreen = false;
	if (useFullscreenProp.compare(L"true") == 0)
		useFullscreen = true;

	// GET THE SCREEN WIDTH AND HEIGHT
	int screenWidth, screenHeight;
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;

	// MAKE A CUSTOM GameOS OBJECT (WindowsOS) FOR SOME WINDOWS
	// PLATFORM STUFF, INCLUDING A Window OF COURSE
	WindowsOS *balloonEscapeOS = new WindowsOS(	hInstance, 
										nCmdShow,
										useFullscreen,
										titleProp,
										screenWidth, screenHeight,
										game);
	
	int textFontSize;
	wstring textFontSizeProp = (*properties)[W_TEXT_FONT_SIZE];
	wstringstream(textFontSizeProp) >> textFontSize;

	// RENDERING WILL BE DONE USING DirectX
	DirectXGraphics *balloonEscapeGraphics = new DirectXGraphics(game);
	balloonEscapeGraphics->init(screenWidth, screenHeight);
	balloonEscapeGraphics->initGraphics(balloonEscapeOS, useFullscreen);
	balloonEscapeGraphics->initTextFont(textFontSize);

	// AND NOW LOAD THE COLORS THE GRAPHICS WILL USE
	// AS A COLOR KEY AND FOR RENDERING TEXT
	initColors(balloonEscapeGraphics, properties);

	// WE'LL USE WINDOWS PLATFORM METHODS FOR GETTING INPUT
	WindowsInput *balloonEscapeInput = new WindowsInput();

	// AND WINDOWS FOR THE TIMER AS WELL
	WindowsTimer *balloonEscapeTimer = new WindowsTimer();

	// NOW INITIALIZE THE Game WITH ALL THE
	// PLATFORM AND GAME SPECIFIC DATA WE JUST CREATED
	game->initPlatformPlugins(	(GameGraphics*)balloonEscapeGraphics,
								(GameInput*)balloonEscapeInput,
								(GameOS*)balloonEscapeOS,
								(GameTimer*)balloonEscapeTimer);

	// LOAD OUR CUSTOM TEXT GENERATOR, WHICH DRAWS
	// TEXT ON THE SCREEN EACH FRAME
	BalloonEscapeTextGenerator *balloonEscapeTextGenerator = new BalloonEscapeTextGenerator();
	balloonEscapeTextGenerator->initText(game);
	GameText *text = game->getText();
	text->initDebugFile(W_DEBUG_FILE);
	text->setTextGenerator((TextGenerator*)balloonEscapeTextGenerator);

	// INIT THE VIEWPORT TOO
	initViewport(game->getGUI(), properties);	

	// WE DON'T NEED THE PROPERTIES MAP ANYMORE, THE GAME IS ALL LOADED
	delete properties;
}

/*
	initColors - this helper method loads the color key, used for loading
	images, and the font color, used for rendering text.
*/
void BalloonEscapeDataLoader::initColors(	GameGraphics *graphics,
									map<wstring,wstring> *properties)
{
	int fontRed, fontGreen, fontBlue;
	wstring fontRedProp = (*properties)[W_FONT_COLOR_RED];
	wstring fontGreenProp = (*properties)[W_FONT_COLOR_GREEN];
	wstring fontBlueProp = (*properties)[W_FONT_COLOR_BLUE];
	wstringstream(fontRedProp) >> fontRed;
	wstringstream(fontGreenProp) >> fontGreen;
	wstringstream(fontBlueProp) >> fontBlue;

	// COLOR USED FOR RENDERING TEXT
	graphics->setFontColor(fontRed, fontGreen, fontBlue);

	int keyRed, keyGreen, keyBlue;
	wstring keyRedProp = (*properties)[W_COLOR_KEY_RED];
	wstring keyGreenProp = (*properties)[W_COLOR_KEY_GREEN];
	wstring keyBlueProp = (*properties)[W_COLOR_KEY_BLUE];
	wstringstream(keyRedProp) >> keyRed;
	wstringstream(keyGreenProp) >> keyGreen;
	wstringstream(keyBlueProp) >> keyBlue;

	// COLOR KEY - COLOR TO BE IGNORED WHEN LOADING AN IMAGE
	// NOTE, IF YOU WISH TO USE PNG IMAGES THAT CONTAIN ALPHA
	// CHANNEL DATA, YOU DON'T NEED A COLOR KEY
	graphics->setColorKey(keyRed, keyGreen, keyBlue);
}

/*
	loadGUI - This method loads all the GUI assets described in the guiInitFile
	argument. Note that we are loading all GUI art for all GUIs when the application
	first starts. We'll learn a better technique later in the semester.
*/
void BalloonEscapeDataLoader::loadGUI(Game *game, wstring guiInitFile)
{
	// WE'RE JUST GOING TO IGNORE THE GUI FILE FOR NOW.
	// FOR THE MOMENT WE ARE CALLING THIS HARD-CODED GUI LOADER
	hardCodedLoadGUIExample(game);
}

/*
	loadLevel - This method should load the data the level described by the
	levelInitFile argument in to the Game's game state manager.
*/
void BalloonEscapeDataLoader::loadWorld(Game *game, wstring levelInitDir, wstring levelInitFile)
{
	// LOAD THE LEVEL'S BACKGROUND TILES
	TMXMapImporter tmxMapImporter;
	tmxMapImporter.loadWorld(game, levelInitDir, levelInitFile);

	// LOAD THE LEVEL'S SPRITE IMAGES
	PoseurSpriteTypesImporter psti;
	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);

	// LET'S MAKE A PLAYER SPRITE
	// @TODO - IT WOULD BE BETTER TO LOAD THIS STUFF FROM A FILE
	GameStateManager *gsm = game->getGSM();
	Physics *physics = gsm->getPhysics();
	physics->setGravity(0);
	SpriteManager *spriteManager = gsm->getSpriteManager();
	AnimatedSprite *player = spriteManager->getPlayer();
	physics->addCollidableObject(player);

	// NOTE THAT RED BOX MAN IS SPRITE ID 2
	AnimatedSpriteType *playerSpriteType = spriteManager->getSpriteType(2);
	player->setSpriteType(playerSpriteType);
	player->setAlpha(255);
	player->setCurrentState(L"IDLE");
	PhysicalProperties *playerProps = player->getPhysicalProperties();
	playerProps->setHP(100);
	playerProps->setDelay(0);
	playerProps->setX(600);
	playerProps->setY(9280);
	playerProps->setZ(1.0f);
	playerProps->setVelocity(0.0f, 0.0f);
	playerProps->setAccelerationX(0);
	playerProps->setAccelerationY(0);
	player->setOnTileThisFrame(false);
	player->setOnTileLastFrame(false);
	player->affixTightAABBBoundingVolume();

}

void BalloonEscapeDataLoader::makeRandomJumpingBot(Game *game, AnimatedSpriteType *randomJumpingBotType, float initX, float initY)
{
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	Physics *physics = game->getGSM()->getPhysics();
	RandomJumpingBot *bot = new RandomJumpingBot(physics, 30, 120, 40);
	physics->addCollidableObject(bot);
	PhysicalProperties *pp = bot->getPhysicalProperties();
	pp->setPosition(initX, initY);
	bot->setSpriteType(randomJumpingBotType);
	bot->setCurrentState(JUMPING);
	bot->setAlpha(255);
	spriteManager->addBot(bot);
	bot->setRemoval(100);
	bot->affixTightAABBBoundingVolume();
}

/*
	initBugginOutGUI - This method builds a GUI for the BugginOut Game application.
	Note that we load all the GUI components from this method, including
	the ScreenGUI with Buttons and Overlays and the Cursor.
*/
void BalloonEscapeDataLoader::hardCodedLoadGUIExample(Game *game)
{
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	DirectXTextureManager *guiTextureManager = (DirectXTextureManager*)graphics->getGUITextureManager();

	// SETUP THE CURSOR VIA OUR HELPER METHOD
	initCursor(gui, guiTextureManager);
	initSplashScreen(game, gui, guiTextureManager);
	initMainMenu(gui, guiTextureManager);
	initInGameGUI(gui, guiTextureManager);
	victoryScreen(game, gui, guiTextureManager);
	helpScreen(game, gui, guiTextureManager);
	aboutScreen(game, gui, guiTextureManager);
	initGameOverScreen(game,gui,guiTextureManager);
}

/*
	initCursor - initializes a simple little cursor for the gui.
*/
void BalloonEscapeDataLoader::initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// SETUP THE CURSOR
	vector<unsigned int> *imageIDs = new vector<unsigned int>();
	int imageID;

	// - FIRST LOAD THE GREEN CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(W_GREEN_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - AND NOW THE RED ONE
	imageID = guiTextureManager->loadTexture(W_RED_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - NOW BUILD AND LOAD THE CURSOR
	Cursor *cursor = new Cursor();
	cursor->initCursor(	imageIDs,
						*(imageIDs->begin()),
						0,
						0,
						0,
						255,
						32,
						32);
	gui->setCursor(cursor);
}

/*
	initSplashScreen - initializes the game's splash screen gui.
*/
void BalloonEscapeDataLoader::helpScreen(Game *game, GameGUI *gui, DirectXTextureManager *guiTextureManager) {
	ScreenGUI *helpScreenGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_HELP_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	helpScreenGUI->addOverlayImage(imageToAdd);

	
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							800,
							600,
							0,
							255,
							game->getGraphics()->getScreenWidth(),
							game->getGraphics()->getScreenHeight(),
							false,
							W_GO_TO_MM_COMMAND);
	helpScreenGUI->addButton(buttonToAdd);


	gui->addScreenGUI(GS_HELP, helpScreenGUI);

}
void BalloonEscapeDataLoader::aboutScreen(Game *game, GameGUI *gui, DirectXTextureManager *guiTextureManager) {
	ScreenGUI *aboutScreenGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_ABOUT_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	aboutScreenGUI->addOverlayImage(imageToAdd);

	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							800,
							600,
							0,
							255,
							game->getGraphics()->getScreenWidth(),
							game->getGraphics()->getScreenHeight(),
							false,
							W_GO_TO_MM_COMMAND);
	aboutScreenGUI->addButton(buttonToAdd);

	gui->addScreenGUI(GS_ABOUT, aboutScreenGUI);
}

void BalloonEscapeDataLoader::initGameOverScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{

	ScreenGUI *gameOverGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_GAME_OVER_SCREEN_PATH);
	
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 199;
	imageToAdd->width = 512;
	imageToAdd->height = 512;
	imageToAdd->imageID = imageID;
	gameOverGUI->addOverlayImage(imageToAdd);


	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							800,
							600,
							0,
							255,
							game->getGraphics()->getScreenWidth(),
							game->getGraphics()->getScreenHeight(),
							false,
							W_GO_TO_MM_COMMAND);
	gameOverGUI->addButton(buttonToAdd);

	gui->addScreenGUI(GS_GAME_OVER, gameOverGUI);



}

void BalloonEscapeDataLoader::victoryScreen(Game *game, GameGUI *gui, DirectXTextureManager *guiTextureManager) {
	ScreenGUI *victoryScreenGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_VICTORY_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1024;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	victoryScreenGUI->addOverlayImage(imageToAdd);

	gui->addScreenGUI(GS_VICTORY, victoryScreenGUI);

}
void BalloonEscapeDataLoader::initSplashScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW, FIRST LET'S ADD A SPLASH SCREEN GUI
	ScreenGUI *splashScreenGUI = new ScreenGUI();

	// WE'LL ONLY HAVE ONE IMAGE FOR OUR GIANT BUTTON
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_SPLASH_SCREEN_PATH);
	unsigned int mouseOverTextureID = normalTextureID;

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							0,
							0,
							0,
							255,
							game->getGraphics()->getScreenWidth(),
							game->getGraphics()->getScreenHeight(),
							false,
							W_GO_TO_MM_COMMAND);
	splashScreenGUI->addButton(buttonToAdd);

	// AND REGISTER IT WITH THE GUI
	gui->addScreenGUI(GS_SPLASH_SCREEN, splashScreenGUI);
}

/*
	initMainMenu - initializes the game's main menu gui.
*/
void BalloonEscapeDataLoader::initMainMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_MAIN_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 256;
	imageToAdd->y = 100;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 512;
	imageToAdd->height = 512;
	imageToAdd->imageID = imageID;
	mainMenuGUI->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN EXIT BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							300,
							500,
							0,
							255,
							200,
							100,
							false,
							W_EXIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD A START BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(W_START_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							300,
							350,
							0,
							255,
							200,
							100,
							false,
							W_START_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	buttonToAdd = new Button();
	normalTextureID = guiTextureManager->loadTexture(W_HELP_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_HELP_IMAGE_MO_PATH);

		// - INIT THE HELP BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							540,
							350,
							0,
							255,
							200,
							100,
							false,
							W_HELP_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	buttonToAdd = new Button();
	normalTextureID = guiTextureManager->loadTexture(W_ABOUT_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_ABOUT_IMAGE_MO_PATH);

		// - INIT THE ABOUT BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							540,
							500,
							0,
							255,
							200,
							100,
							false,
							W_ABOUT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);
	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_MAIN_MENU,		mainMenuGUI);
}

/*
	initInGameGUI - initializes the game's in-game gui.
*/
void BalloonEscapeDataLoader::initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW ADD THE IN-GAME GUI
	ScreenGUI *inGameGUI = new ScreenGUI();

	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);

	//LIFE BAR
	vector <unsigned int> lifeBarsID;
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_0_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_1_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_2_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_3_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_4_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_5_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_6_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_7_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_8_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_9_PATH));
	lifeBarsID.push_back(guiTextureManager->loadTexture(W_LIFEBAR_10_PATH));

	LifeStatus *imageToAdd = new LifeStatus();
	imageToAdd->initLifeStatus(lifeBarsID,750,23,0,255,244,21,0);
	inGameGUI->addLifeStatus(imageToAdd);

	//LIVES
	vector <unsigned int> livesID;
	livesID.push_back(guiTextureManager->loadTexture(W_EXTRA_LIVES_2_PATH));
	livesID.push_back(guiTextureManager->loadTexture(W_EXTRA_LIVES_1_PATH));
	livesID.push_back(guiTextureManager->loadTexture(W_EXTRA_LIVES_0_PATH));

	LifeStatus *imageToAdd2 = new LifeStatus();
	imageToAdd2->initLifeStatus(livesID,450,20,0,255,97,24,1);
	inGameGUI->addLifeStatus(imageToAdd2);

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							0,
							0,
							0,
							255,
							200,
							100,
							false,
							W_QUIT_COMMAND);
	inGameGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_GAME_IN_PROGRESS,	inGameGUI);
}

/*
	initViewport - initializes the game's viewport.
*/
void BalloonEscapeDataLoader::initViewport(GameGUI *gui, map<wstring,wstring> *properties)
{
	// AND NOW SPECIFY THE VIEWPORT SIZE AND LOCATION. NOTE THAT IN THIS EXAMPLE,
	// WE ARE PUTTING A TOOLBAR WITH A BUTTON ACCROSS THE NORTH OF THE APPLICATION.
	// THAT TOOLBAR HAS A HEIGHT OF 64 PIXELS, SO WE'LL MAKE THAT THE OFFSET FOR
	// THE VIEWPORT IN THE Y AXIS
	Viewport *viewport = gui->getViewport();

	int viewportOffsetX, viewportOffsetY, toggleOffsetY, screenWidth, screenHeight;
	wstring viewportOffsetXProp = (*properties)[W_VIEWPORT_OFFSET_X];
	wstring viewportOffsetYProp = (*properties)[W_VIEWPORT_OFFSET_Y];
	wstring toggleOffsetYProp = (*properties)[W_TOGGLE_OFFSET_Y];
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(viewportOffsetXProp) >> viewportOffsetX;
	wstringstream(viewportOffsetYProp) >> viewportOffsetY;
	wstringstream(toggleOffsetYProp) >> toggleOffsetY;
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;
	int viewportWidth = screenWidth - viewportOffsetX;
	int viewportHeight = screenHeight - viewportOffsetY;
	viewport->setViewportWidth(viewportWidth);
	viewport->setViewportHeight(viewportHeight);
	viewport->setViewportOffsetX(viewportOffsetX);
	viewport->setViewportOffsetY(viewportOffsetY);
	viewport->setToggleOffsetY(toggleOffsetY);
}