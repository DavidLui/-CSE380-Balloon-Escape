#include "sssf\game\Game.h"
#include "sssf\gsm\physics\Collision.h"
#include "balloon_escape\BalloonEscapeCollisionListener.h"


// ANIMATED SPRITE TYPE LOADING
#include "psti\PoseurSpriteTypesImporter.h"



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


boolean deadonce = false;
void BalloonEscapeCollisionListener::respondToCollision(Game *game, Collision *collision)
{
	// NOTE FROM THE COLLIDABLE OBJECTS, WHICH ARE IN THE COLLISION,
	// WE CAN CHECK AND SEE ON WHICH SIDE THE COLLISION HAPPENED AND
	// CHANGE SOME APPROPRIATE STATE ACCORDINGLY
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	PhysicalProperties *pp = player->getPhysicalProperties();
	//AnimatedSprite *bot = collision
	CollidableObject *sprite2 = collision->getCO2();
	PhysicalProperties *pp2 = sprite2->getPhysicalProperties();
	AnimatedSprite *bot = (AnimatedSprite*)sprite2;
	if (!collision->isCollisionWithTile() && player->getCurrentState() != L"DYING")
	{
		CollidableObject *sprite = collision->getCO1();

		if (sprite2->getPhysicalProperties()->getZ() == 1.0f) {
			
			bot = (AnimatedSprite*)sprite;
				 pp = sprite2->getPhysicalProperties();
					pp2 = sprite->getPhysicalProperties();

			sprite = collision->getCO2();
			sprite2 = collision->getCO1();
			if (sprite->getCollisionEdge() == BOTTOM_EDGE)
			{	
				bot->setCurrentState(L"DYING");
				pp2->setVelocity(0.0f, 0.0f);
				pp2->setAccelerationX(0);
				pp2->setAccelerationY(0);
				// ENEMY IS DEAD - WE SHOULD PLAY A DEATH ANIMATION
				// AND MARK IT FOR REMOVAL
			}
			else if (bot->getCurrentState() != L"DYING")
			{
				if (pp->getDelay() == 0) {
					if (pp->getHP() == 10 ) {
						//lives->setCurrentState(L"TWO");
						if(deadonce == true)
						//lives->setCurrentState(L"ONE");
						player->setCurrentState(L"DYING");
						pp->setDelay(90);
						pp->setVelocity(0.0f, 0.0f);
						pp->setAccelerationX(0);
						pp->setAccelerationY(0);
						deadonce=true;
					}
					else {
						pp->setDelay(90);
						pp->setHP(pp->getHP()-10);
						SpriteManager *spriteManager = gsm->getSpriteManager();
						AnimatedSpriteType *yellowman = spriteManager->getSpriteType(3);
						player->setSpriteType(yellowman);
					}
				}

				// PLAYER IS DEAD - WE SHOULD PLAY A DEATH ANIMATION
				// AND MARK IT FOR REMOVAL/RESPAWN/RESTART GAME, WHATEVER
				// THE DEMANDS OF THE GAME ARE
			}
		}
		else if(sprite->getPhysicalProperties()->getZ() == 1.0f) {
			PhysicalProperties *pp = sprite->getPhysicalProperties();
			if (sprite->getCollisionEdge() == BOTTOM_EDGE)
			{
				
				bot->setCurrentState(L"DYING");
				pp2->setVelocity(0.0f, 0.0f);
				pp2->setAccelerationX(0);
				pp2->setAccelerationY(0);
				// ENEMY IS DEAD - WE SHOULD PLAY A DEATH ANIMATION
				// AND MARK IT FOR REMOVAL

			}
			else if (bot->getCurrentState() != L"DYING")
			{
				if (pp->getDelay() == 0) {
					if (pp->getHP() == 10 ) {


						//lives->setCurrentState(L"TWO");
						if(deadonce == true)
						//lives->setCurrentState(L"ONE");
						player->setCurrentState(L"DYING");
						pp->setDelay(90);
						pp->setVelocity(0.0f, 0.0f);
						pp->setAccelerationX(0);
						pp->setAccelerationY(0);
						deadonce=true;

					}
					else {
						pp->setDelay(90);
						pp->setHP(pp->getHP()-10);
						SpriteManager *spriteManager = gsm->getSpriteManager();
						AnimatedSpriteType *yellowman = spriteManager->getSpriteType(3);
						player->setSpriteType(yellowman);
					}
				}

				// PLAYER IS DEAD - WE SHOULD PLAY A DEATH ANIMATION
				// AND MARK IT FOR REMOVAL/RESPAWN/RESTART GAME, WHATEVER
				// THE DEMANDS OF THE GAME ARE
			}
		}
	}

	if (pp->getDelay() == 0) {
			SpriteManager *spriteManager = gsm->getSpriteManager();
			AnimatedSpriteType *redman = spriteManager->getSpriteType(2);
			player->setSpriteType(redman);
	}
}