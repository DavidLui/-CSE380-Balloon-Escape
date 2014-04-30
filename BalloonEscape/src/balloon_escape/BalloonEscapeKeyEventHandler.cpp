/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BalloonEscapeKeyEventHandler.cpp

	See BalloonEscapeKeyEventHandler.h for a class description.
*/

#include "balloon_escape_VS\stdafx.h"
#include "balloon_escape\BalloonEscape.h"
#include "balloon_escape\BalloonEscapeKeyEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\game\WStringTable.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsTimer.h"
#include "Box2D\Box2D.h"
/*
	handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
	gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
	key states since the last frame, which can allow us to respond to key presses, including when keys
	are held down for multiple frames.
*/
bool jumping = true;

int counts;
void BalloonEscapeKeyEventHandler::handleKeyEvents(Game *game)
{
	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	PhysicalProperties *pp = player->getPhysicalProperties();
	Viewport *viewport = game->getGUI()->getViewport();
	AnimatedSprite *HP = gsm->getSpriteManager()->getHealthBar();
	PhysicalProperties *HPP = HP->getPhysicalProperties();
	
	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		
		if (pp->getHP() == 100)
			HP->setCurrentState(L"HUNDRED");
		else if (pp->getHP() == 90)
			HP->setCurrentState(L"NINETY");
		else if (pp->getHP() == 80)
			HP->setCurrentState(L"EIGHTY");
		else if (pp->getHP() == 70)
			HP->setCurrentState(L"SEVENTY");
		else if (pp->getHP() == 60)
			HP->setCurrentState(L"SIXTY");
		else if (pp->getHP() == 50)
			HP->setCurrentState(L"FIFTY");
		else if (pp->getHP() == 40)
			HP->setCurrentState(L"FORTY");
		else if (pp->getHP() == 30)
			HP->setCurrentState(L"THIRTY");
		else if (pp->getHP() == 20)
			HP->setCurrentState(L"TWENTY");
		else if (pp->getHP() == 10)
			HP->setCurrentState(L"TEN");
		if (pp->getDelay() > 0) {
			pp->setDelay(pp->getDelay()-1);
		}
		if (player->getCurrentState() == L"DYING" && pp->getDelay() == 0) {
			player->setCurrentState(L"IDLE");
			pp->setHP(100);
		}
	
		// WASD KEY PRESSES WILL CONTROL THE PLAYER
		// SO WE'LL UPDATE THE PLAYER VELOCITY WHEN THESE KEYS ARE
		// PRESSED, THAT WAY PHYSICS CAN CORRECT AS NEEDED
		float vX = pp->getVelocityX();
		float vY = pp->getVelocityY();

		// YOU MIGHT WANT TO UNCOMMENT THIS FOR SOME TESTING,
		// BUT IN THIS ASSIGNMENT, THE USER MOVES VIA MOUSE BUTTON PRESSES
		
		if (player->getCurrentState() != L"DYING"){
		if (input->isKeyDown(A_KEY))
		{
			vX = -PLAYER_SPEED;
			player->setCurrentState(FLYING_LEFT);
	
			//player->getBody()->ApplyLinearImpulse(b2Vec2(-300,0), player->getBody()->GetWorldCenter(), true);
			player->getBody()->SetTransform(b2Vec2(player->getPhysicalProperties()->getX()-10.0f,player->getPhysicalProperties()->getY()), 0);
		}
		else if (input->isKeyDown(D_KEY))
		{
			vX = PLAYER_SPEED;
			player->setCurrentState(FLYING_RIGHT);
			player->getBody()->SetTransform(b2Vec2(player->getPhysicalProperties()->getX()+10.0f,player->getPhysicalProperties()->getY()), 0);
		}
		else if (input->isKeyDownForFirstTime(G_KEY))
		{
			viewport->toggleDebugView();
			game->getGraphics()->toggleDebugTextShouldBeRendered();
		}
		else
		{
			vX = 0.0f;
			player->setCurrentState(IDLE);
		}
		if (input->isKeyDownForFirstTime(SPACE_KEY))
		{
		
		}

	}

		if (input->isKeyDownForFirstTime(P_KEY))
		{
			gsm->getPhysics()->togglePhysics();
		}
		if (input->isKeyDownForFirstTime(T_KEY))
		{
			gsm->getPhysics()->activateForSingleUpdate();
		}
		//Test to change level
		/*if (pp->getY() <= 9000.0F) {
			GameStateManager *gsm = game->getGSM();
			if(gsm->getCurrentLevel() == 3)
				gsm->Victory();
			else if (gsm->getCurrentLevel() == 2)
			{
				gsm->unloadCurrentLevel();
				gsm->loadLevel(game, W_LEVEL_3_NAME);
			}
			else
			{
				gsm->unloadCurrentLevel();
				gsm->loadLevel(game, W_LEVEL_2_NAME);
			}
		}*/

		// NOW SET THE ACTUAL PLAYER VELOCITY
 		pp->setVelocity(vX, vY);
		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		float p = player->getPhysicalProperties()->getY();
		float e = (float)viewport->getViewportY();
		if (player->getPhysicalProperties()->getY() > (float)viewport->getViewportY()) {
			viewportVy -= 1;
			viewportMoved = true;
		}
		else {
			viewportVy = 0;
		}
		if (input->isKeyDown(UP_KEY))
		{
			viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(DOWN_KEY))
		{
			viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}

		Viewport *viewport = game->getGUI()->getViewport();
		if (viewportMoved)
			viewport->moveViewport((int)floor(viewportVx+0.5f), (int)floor(viewportVy+0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());
		
	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;		
		cursor->setActiveCursorID(id);
	}

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	WindowsTimer *timer = (WindowsTimer*)game->getTimer();
	int fps = timer->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		timer->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		timer->setTargetFPS(fps - FPS_INC);
}